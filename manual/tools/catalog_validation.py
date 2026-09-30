"""Cross-catalog identity, source-path, and typed-relationship validation."""

from pathlib import Path
import re

import yaml

import versioning


COMMAND_TABLES = ("registered_commands", "fixed_controls", "launch_options")
PAGE_CATALOGS = {
    "system": ("systems", "systems"),
    "guide": ("guides", "guides"),
    "using": ("using", "using"),
    "internal": ("internals", "internals"),
}
RELATED_COLLECTIONS = (
    ("content/scripting", "**/*.md", None),
    ("content/systems", "*.md", "keys"),
    ("content/guides", "*.md", "uses_keys"),
    ("content/using", "*.md", None),
    ("content/internals", "*.md", None),
    ("content/formats", "*.md", None),
)
_FRONTMATTER = re.compile(r"^---\r?\n([\s\S]*?)\r?\n---")


def frontmatter(path, errors=None, context=None):
    label = context or str(path)
    try:
        source = Path(path).read_text(encoding="utf-8")
        match = _FRONTMATTER.match(source)
        if not match:
            raise ValueError("missing YAML frontmatter")
        data = yaml.safe_load(match.group(1)) or {}
        if not isinstance(data, dict):
            raise ValueError("frontmatter must be a mapping")
        return data
    except (OSError, ValueError, yaml.YAMLError) as error:
        if errors is None:
            raise
        errors.append(f"{label}: {error}")
        return {}


def validate_commands(errors, manual):
    manual = Path(manual)
    path = manual / "data" / "commands.yaml"
    try:
        with path.open(encoding="utf-8") as stream:
            data = yaml.safe_load(stream) or {}
    except (OSError, yaml.YAMLError) as error:
        errors.append(f"manual/data/commands.yaml: cannot load command catalog: {error}")
        return {}

    records = {}
    routes = {}
    for table in COMMAND_TABLES:
        rows = data.get(table, [])
        if not isinstance(rows, list):
            continue
        for position, row in enumerate(rows, start=1):
            if not isinstance(row, dict):
                continue
            identifier = row.get("id")
            route = row.get("route_id")
            context = f"manual/data/commands.yaml {table} entry {position}"
            if not isinstance(identifier, str) or not identifier:
                continue
            if identifier in records:
                errors.append(f"{context}: duplicate command ID {identifier!r}")
                continue
            if isinstance(route, str) and route in routes:
                errors.append(
                    f"{context}: command route {route!r} is already owned by {routes[route]!r}")
            elif isinstance(route, str):
                routes[route] = identifier
            records[identifier] = row

    seen_overlays = {}
    for overlay in sorted((manual / "content" / "commands").glob("*.md")):
        label = str(overlay.relative_to(manual))
        data = frontmatter(overlay, errors, label)
        identifier = data.get("command_id")
        if not isinstance(identifier, str) or not identifier:
            continue
        record = records.get(identifier)
        if record is None:
            errors.append(
                f"{label}: unknown command ID {identifier!r}; preserve exact case and run manage.py update")
            continue
        if identifier in seen_overlays:
            errors.append(
                f"{label}: duplicate command overlay; already provided by {seen_overlays[identifier]}")
        else:
            seen_overlays[identifier] = label
        expected = f"{record.get('route_id')}.md"
        if overlay.name != expected:
            errors.append(
                f"{label}: filename must be {expected}; create it with: "
                f"python manual/tools/manage.py scaffold command {identifier}")
    return records


def active_page_entities(errors, manual, commands):
    manual = Path(manual)
    entities = {"command": commands}
    for entity_type, (folder, prefix) in PAGE_CATALOGS.items():
        records = {}
        for path in sorted((manual / "content" / folder).glob("*.md")):
            identifier = path.stem
            data = frontmatter(path, errors, str(path.relative_to(manual)))
            records[identifier] = {
                **data,
                "route": f"/{prefix}/{identifier}/",
            }
        entities[entity_type] = records
    return entities


def validate_using_sources(errors, manual, entities):
    root = Path(manual).parent
    for identifier, record in entities.get("using", {}).items():
        for source in record.get("source_files", []):
            if not isinstance(source, str):
                continue
            candidate = Path(source)
            if candidate.is_absolute() or ".." in candidate.parts:
                errors.append(f"using:{identifier}: invalid source path {source!r}")
            elif not (root / candidate).is_file():
                errors.append(f"using:{identifier}: source path does not exist: {source}")


def validate_relations(
        errors, manual, keys, scripting, formats, tombstones, enums, entities):
    manual = Path(manual)
    scripts = versioning.scripting_catalog(scripting)
    tombstone_map = {
        (row.get("type"), row.get("id")): row for row in tombstones
    }
    for folder, pattern, key_shortcut in RELATED_COLLECTIONS:
        for path in sorted((manual / folder).glob(pattern)):
            label = str(path.relative_to(manual))
            data = frontmatter(path, errors, label)
            shortcuts = set(data.get(key_shortcut, [])) if key_shortcut else set()
            for position, reference in enumerate(data.get("related", []), start=1):
                if (isinstance(reference, dict)
                        and reference.get("type") == "key"
                        and reference.get("id") in shortcuts
                        and reference.get("scope") is None):
                    errors.append(
                        f"{label} related entry {position}: key {reference.get('id')!r} "
                        f"is already present in {key_shortcut}")
                versioning.validate_reference(
                    errors,
                    reference,
                    f"{label} related entry {position}",
                    keys,
                    scripts,
                    formats,
                    tombstone_map,
                    enums,
                    entities,
                )

"""Validate current generated data, authored content, and branch-relative changes."""

import json
from pathlib import Path
import re

import yaml
import enum_drift
import catalog_validation
import formats as format_catalogs
import versioning


MANUAL = Path(__file__).resolve().parents[1]
SITE = MANUAL / "site"
SEMANTIC_SCOPE_FIELDS = (
    "applies_to", "file", "section", "value_type", "note", "precedence", "read_from"
)
OMISSION_KINDS = {"value", "computed", "inherited", "unchanged", "context-dependent"}
SCRIPTING_TABLES = {
    "actions": "trigger_actions",
    "events": "trigger_events",
    "missions": "team_missions",
}


def read_yaml(path):
    with Path(path).open(encoding="utf-8") as stream:
        return yaml.safe_load(stream)


def frontmatter(path):
    source = path.read_text(encoding="utf-8")
    match = re.match(r"^---\r?\n([\s\S]*?)\r?\n---", source)
    if not match:
        raise ValueError(f"{path.relative_to(MANUAL)}: missing YAML frontmatter")
    return yaml.safe_load(match.group(1)) or {}


def slugify(text):
    return re.sub(r"^-|-+$", "", re.sub(r"[^a-z0-9]+", "-", str(text).lower()))


def key_route(name, entry):
    route = name.lower()
    if entry.get("case_collides_with"):
        route += "-" + slugify(entry["scopes"][0]["applies_to"][0] or "global")
    return route


def scope_route_base(scope):
    return slugify((scope.get("applies_to") or [scope.get("section", "global")])[0])


def scope_route_signature(scope):
    """The published fields that order two scopes sharing one route id.

    Suffixed scope routes (`client-settings-2`) are handed out by position, so
    the published URL of a scope depends on where its read landed in the
    extractor's record list. The extractor orders such scopes by their own
    recorded content instead; this is the same ordering over the fields that
    survive into public data, so a catalog that lost it fails validation rather
    than quietly swapping two routes.
    """

    return (
        scope.get("level") or "",
        scope.get("file") or "",
        scope.get("value_type") or "",
        json.dumps(scope.get("section"), sort_keys=True, separators=(",", ":")),
        json.dumps(sorted(scope.get("applies_to") or []), separators=(",", ":")),
        scope.get("note") or "",
        scope.get("precedence") or "",
    )


def scope_route_order_errors(name, scopes):
    """Report scopes whose suffixed route would depend on extraction order."""

    errors = []
    ordered_bases = {}
    for scope in scopes:
        base = scope_route_base(scope)
        signature = scope_route_signature(scope)
        if base in ordered_bases and signature < ordered_bases[base]:
            errors.append(
                f"{name}: scopes sharing the route id {base!r} are out of their "
                "recorded order, so the suffixed route would depend on "
                "extraction order; run manual/tools/manage.py update")
        ordered_bases[base] = signature
    return errors


def scope_route_ids(entry):
    routes = []
    for raw in entry.get("scopes", []):
        base = scope_route_base(raw)
        candidate, suffix = base, 2
        while candidate in routes:
            candidate = f"{base}-{suffix}"
            suffix += 1
        routes.append(candidate)
    return routes


def semantic_key(entry):
    scopes = [
        {field: scope[field] for field in SEMANTIC_SCOPE_FIELDS if field in scope}
        for scope in entry.get("scopes", [])
    ]
    return sorted(json.dumps(scope, sort_keys=True, separators=(",", ":")) for scope in scopes)


def classify_key_deltas(current, base):
    current_names, base_names = set(current), set(base)
    return {
        "added": current_names - base_names,
        "changed": {
            key for key in current_names & base_names
            if semantic_key(current[key]) != semantic_key(base[key])
        },
        "removed": base_names - current_names,
    }


def scripting_semantic_row(row):
    normalized = dict(row)
    index = normalized.pop("index", None)
    example = normalized.get("ini_example")
    if isinstance(example, dict) and isinstance(example.get("line"), str):
        normalized["ini_example"] = dict(example)
        prefix = f"<TriggerID>=1,{index},"
        normalized["ini_example"]["line"] = example["line"].replace(
            prefix, "<TriggerID>=1,<Index>,", 1)
    return normalized


def classify_scripting_deltas(current, base):
    result = {}
    for label, table in SCRIPTING_TABLES.items():
        current_rows = {row["id"]: row for row in current.get(table, [])}
        base_rows = {row["id"]: row for row in base.get(table, [])}
        shared = set(current_rows) & set(base_rows)
        result[label] = {
            "added": set(current_rows) - set(base_rows),
            "changed": {
                row_id for row_id in shared
                if scripting_semantic_row(current_rows[row_id])
                != scripting_semantic_row(base_rows[row_id])
            },
            "removed": set(base_rows) - set(current_rows),
            "shifted": {
                row_id: (base_rows[row_id].get("index"), current_rows[row_id].get("index"))
                for row_id in shared
                if base_rows[row_id].get("index") != current_rows[row_id].get("index")
            },
        }
    return result


def validate_keys(errors):
    current = read_yaml(MANUAL / "data" / "ini-keys.yaml")
    if not isinstance(current, dict) or not current:
        errors.append("current INI key data must be a non-empty mapping")
        return {}, {}

    if "Inaccuate" in current:
        errors.append("unproven prototype-only key Inaccuate must not be published")

    routes = {}
    for name, entry in current.items():
        route = key_route(name, entry)
        if route in routes:
            errors.append(f"route collision: {name} and {routes[route]} -> {route}")
        routes[route] = name
        if not entry.get("scopes"):
            errors.append(f"{name}: no extracted scopes")
        for scope in entry.get("scopes", []):
            for field in ("applies_to", "file", "section", "value_type", "status", "_provenance"):
                if field not in scope:
                    errors.append(f"{name}: scope missing {field}")
            if "default" in scope:
                errors.append(f"{name}: public default field must not be generated")
            provenance = scope.get("_provenance") or {}
            if "default_candidate" not in provenance:
                errors.append(f"{name}: provenance missing default_candidate")
        errors.extend(scope_route_order_errors(name, entry.get("scopes", [])))

    omission_claims = {}
    for path in (MANUAL / "content" / "keys").glob("*.md"):
        data = frontmatter(path)
        key = data.get("key")
        if key not in current:
            errors.append(f"{path.relative_to(MANUAL)}: unknown key {key}")
            continue

        routes_for_key = scope_route_ids(current[key])
        scope = data.get("scope")
        if scope and scope not in routes_for_key:
            errors.append(f"{path.relative_to(MANUAL)}: unknown scope {scope}")

        when_omitted = data.get("when_omitted")
        if when_omitted is None:
            continue
        if scope is None and len(routes_for_key) > 1:
            errors.append(
                f"{path.relative_to(MANUAL)}: when_omitted on a multi-scope parent is "
                "never rendered; record it on the scoped overlays instead")
            continue
        if not isinstance(when_omitted, dict):
            errors.append(f"{path.relative_to(MANUAL)}: when_omitted must be a mapping")
            continue
        kind = when_omitted.get("kind")
        if kind not in OMISSION_KINDS:
            errors.append(f"{path.relative_to(MANUAL)}: invalid when_omitted kind {kind!r}")
            continue
        unexpected = set(when_omitted) - {"kind", "value", "note"}
        if unexpected:
            errors.append(
                f"{path.relative_to(MANUAL)}: unexpected when_omitted fields {sorted(unexpected)}")
        if kind == "value":
            if "value" not in when_omitted or not isinstance(when_omitted.get("value"), str):
                errors.append(
                    f"{path.relative_to(MANUAL)}: value omission requires a string value")
            if "note" in when_omitted and (
                    not isinstance(when_omitted["note"], str) or not when_omitted["note"].strip()):
                errors.append(
                    f"{path.relative_to(MANUAL)}: omission note must be a non-empty string")
        else:
            if "value" in when_omitted:
                errors.append(
                    f"{path.relative_to(MANUAL)}: {kind} omission cannot declare value")
            if not isinstance(when_omitted.get("note"), str) or not when_omitted["note"].strip():
                errors.append(
                    f"{path.relative_to(MANUAL)}: {kind} omission requires a note")

        if not scope:
            if len(routes_for_key) != 1:
                errors.append(
                    f"{path.relative_to(MANUAL)}: multi-scope key requires scoped omission metadata")
                continue
            scope = routes_for_key[0]
        claim = (key, scope)
        if claim in omission_claims:
            errors.append(
                f"{path.relative_to(MANUAL)}: duplicate omission claim; "
                f"already declared by {omission_claims[claim].relative_to(MANUAL)}")
        else:
            omission_claims[claim] = path

    return current, omission_claims


def validate_required_omissions(errors, current, omission_claims, required_keys):
    for key in sorted(required_keys):
        if key not in current:
            continue
        for scope in scope_route_ids(current[key]):
            if (key, scope) not in omission_claims:
                errors.append(
                    f"{key}[{scope}]: authored when_omitted metadata is required "
                    "for an added or semantically changed key")


def validate_required_omission_targets(
        errors, current, omission_claims, required_targets):
    for key, requested_scope in sorted(
            required_targets, key=lambda item: (item[0] or "", item[1] or "")):
        if key not in current:
            continue
        scopes = [requested_scope] if requested_scope else scope_route_ids(current[key])
        for scope in scopes:
            if (key, scope) not in omission_claims:
                errors.append(
                    f"{key}[{scope}]: authored when_omitted metadata is required "
                    "for an added or behavior-changed key")


def validate_authored(errors, current):
    guide_ids = {path.stem for path in (MANUAL / "content" / "guides").glob("*.md")}
    system_ids = {path.stem for path in (MANUAL / "content" / "systems").glob("*.md")}

    for path in (MANUAL / "content" / "keys").glob("*.md"):
        data = frontmatter(path)
        for reference in data.get("see_also", []):
            if reference in current:
                continue
            if reference.startswith("guide:") and reference[6:] in guide_ids:
                continue
            if reference.startswith("system:") and reference[7:] in system_ids:
                continue
            errors.append(f"{path.relative_to(MANUAL)}: invalid see_also target {reference}")

    for folder, relation in (("guides", "uses_keys"), ("systems", "keys")):
        for path in (MANUAL / "content" / folder).glob("*.md"):
            data = frontmatter(path)
            for key in data.get(relation, []):
                if key not in current:
                    errors.append(f"{path.relative_to(MANUAL)}: unknown key {key}")

INTERNAL_CATEGORIES = {
    "architecture", "simulation-systems", "data-scripting",
    "rendering-media", "networking-persistence",
}


def validate_internals(errors):
    records = {}
    for path in (MANUAL / "content" / "internals").glob("*.md"):
        data = frontmatter(path)
        label = str(path.relative_to(MANUAL))
        records[path.stem] = data
        if not isinstance(data.get("title"), str) or not data["title"].strip():
            errors.append(f"{label}: missing title")
        if not isinstance(data.get("summary"), str) or not data["summary"].strip():
            errors.append(f"{label}: missing summary")
        if data.get("category") not in INTERNAL_CATEGORIES:
            errors.append(f"{label}: invalid Internals category {data.get('category')!r}")
        source_files = data.get("source_files")
        if not isinstance(source_files, list) or not source_files:
            errors.append(f"{label}: source_files must be a non-empty list")
            continue
        for source_file in source_files:
            if (not isinstance(source_file, str) or not source_file
                    or Path(source_file).is_absolute() or ".." in Path(source_file).parts):
                errors.append(f"{label}: invalid source path {source_file!r}")
            elif not (MANUAL.parent / source_file).is_file():
                errors.append(f"{label}: source path does not exist: {source_file}")
    return records

def validate_scripting(errors):
    data = read_yaml(MANUAL / "data" / "scripting.yaml")
    if not isinstance(data, dict):
        errors.append("current scripting data must be a mapping")
        return {}

    need_shapes = {}
    for kind, table in SCRIPTING_TABLES.items():
        rows = data.get(table, [])
        if not rows:
            errors.append(f"{kind}: generated table must not be empty")
            continue
        indexes = [row.get("index") for row in rows]
        if indexes != list(range(len(rows))):
            errors.append(f"{kind}: numeric IDs are not contiguous from zero")
        ids = [row.get("id") for row in rows]
        if len(ids) != len(set(ids)):
            errors.append(f"{kind}: generated IDs must be unique")
        for row in rows:
            if not row.get("id") or not row.get("editor_name") or not row.get("editor_description"):
                errors.append(f"{kind} {row.get('index')}: incomplete generated editor metadata")
            if "parameter" in row:
                errors.append(f"{kind} {row.get('index')}: legacy singular parameter field")
            need, parameters = row.get("need"), row.get("parameters")
            if not isinstance(need, str) or not need.startswith("NEED_"):
                errors.append(f"{kind} {row.get('index')}: missing raw need token")
            if not isinstance(parameters, list):
                errors.append(f"{kind} {row.get('index')}: parameters must be an array")
                continue
            example = row.get("ini_example")
            if kind in ("actions", "events"):
                expected_section = "[Actions]" if kind == "actions" else "[Events]"
                expected_prefix = f"<TriggerID>=1,{row.get('index')},"
                if (not isinstance(example, dict) or set(example) != {"section", "line"}
                        or example.get("section") != expected_section
                        or not isinstance(example.get("line"), str)
                        or not example["line"].startswith(expected_prefix)):
                    errors.append(f"{kind} {row.get('index')}: invalid generated INI example")
            elif "ini_example" in row:
                errors.append(f"missions {row.get('index')}: missions must not carry INI examples")
            for position, parameter in enumerate(parameters, start=1):
                if not isinstance(parameter, dict) or set(parameter) != {"name", "type"}:
                    errors.append(
                        f"{kind} {row.get('index')} parameter {position}: expected name and type")
                    continue
                if not all(isinstance(parameter[field], str) and parameter[field].strip()
                           for field in ("name", "type")):
                    errors.append(
                        f"{kind} {row.get('index')} parameter {position}: empty name or type")
            shape = json.dumps(parameters, sort_keys=True)
            if need in need_shapes and need_shapes[need] != shape:
                errors.append(f"{kind} {row.get('index')}: inconsistent parameters for {need}")
            else:
                need_shapes[need] = shape

    rows_by_type = {
        singular: data.get(table, [])
        for _, (table, singular) in versioning.SCRIPTING_TYPES.items()
    }
    for path in (MANUAL / "content" / "scripting").glob("**/*.md"):
        authored = frontmatter(path)
        entity_type, entity_id = authored.get("type"), authored.get("id")
        rows = rows_by_type.get(entity_type)
        if rows is None or entity_id not in {row["id"] for row in rows}:
            errors.append(f"{path.relative_to(MANUAL)}: no matching generated scripting record")
    return data


def validate_formats(errors, keys):
    return format_catalogs.validate_formats(errors, keys, MANUAL)


def normalize_base_registry(raw):
    if not isinstance(raw, dict) or not isinstance(raw.get("releases"), list):
        return None
    rows = []
    development = None
    for row in raw["releases"]:
        if not isinstance(row, dict) or not isinstance(row.get("version"), str):
            continue
        normalized = dict(row)
        try:
            normalized["_parsed"] = versioning.Version(row["version"])
        except ValueError:
            normalized["_parsed"] = None
        rows.append(normalized)
        if row.get("status") == "development":
            development = row["version"]
    return {
        "rows": rows,
        "by_version": {row["version"]: row for row in rows},
        "development": development,
    }


def classify_enum_deltas(current, base_records, base_signatures):
    current_ids = set(current)
    base_ids = set(base_records or {})
    signatures = base_signatures or {}
    added = {
        enum_id for enum_id in current_ids
        if signatures.get(enum_id) is None
    }
    changed = {
        enum_id for enum_id in current_ids
        if signatures.get(enum_id) is not None
        and tuple(current[enum_id].get("_signature") or ()) != tuple(signatures[enum_id])
    }
    removed = base_ids - current_ids
    route_changed = {
        enum_id for enum_id in current_ids & base_ids
        if current[enum_id].get("slug") != base_records[enum_id].get("slug")
    }
    return {
        "added": added,
        "changed": changed,
        "removed": removed,
        "route_changed": route_changed,
    }


def classify_command_deltas(current, base):
    current_records = versioning.command_catalog(current)
    base_records = versioning.command_catalog(base)
    current_ids = set(current_records)
    base_ids = set(base_records)

    def semantic(record):
        # Titles are presentation naming; command identity is the id and the
        # behavioral fields. Renaming a command is a documentation change and
        # needs no lifecycle record.
        #
        # A registered command's description is the engine's own registered
        # text, so a change there is an engine change. A fixed control's or a
        # launch option's description is authored copy in command-adapters.yaml
        # like its title, and correcting the wording is documentation work.
        ignored = {"id", "route_id", "title", "_provenance"}
        if record.get("kind") in {"fixed", "launch"}:
            ignored.add("description")
        return {
            field: value for field, value in record.items()
            if field not in ignored
        }

    return {
        "added": current_ids - base_ids,
        "changed": {
            entity_id for entity_id in current_ids & base_ids
            if semantic(current_records[entity_id]) != semantic(base_records[entity_id])
        },
        "removed": base_ids - current_ids,
        "route_changed": {
            entity_id for entity_id in current_ids & base_ids
            if current_records[entity_id].get("route_id")
            != base_records[entity_id].get("route_id")
        },
    }


def validate_routes(errors):
    literal_link = re.compile(r"(?:href|src)=[\"']/")
    literal_config_link = re.compile(r"\blink:\s*[\"']/")
    for path in (SITE / "src").glob("**/*"):
        if path.suffix not in {".astro", ".ts", ".js", ".mjs"}:
            continue
        if path.name in {"paths.ts", "rehype-base-links.mjs"}:
            continue
        source = path.read_text(encoding="utf-8")
        if literal_link.search(source) or literal_config_link.search(source):
            errors.append(f"{path.relative_to(MANUAL)}: unhandled root-relative link")


def validate_all(base=None):
    errors = []
    if base is not None and "keys" not in base:
        base = {"keys": base}

    current, omission_claims = validate_keys(errors)
    validate_authored(errors, current)
    internals = validate_internals(errors)
    enums = enum_drift.validate_enums(errors, MANUAL, MANUAL.parent)
    scripting = validate_scripting(errors)
    formats = validate_formats(errors, current)
    commands = catalog_validation.validate_commands(errors, MANUAL)
    entities = catalog_validation.active_page_entities(errors, MANUAL, commands)
    catalog_validation.validate_using_sources(errors, MANUAL, entities)
    registry = versioning.validate_releases(errors, MANUAL, MANUAL.parent)
    base_registry = normalize_base_registry(base.get("releases")) if base else None
    versioning.validate_released_registry_history(errors, registry, base_registry)

    tombstones = versioning.validate_tombstones(
        errors, MANUAL, current, scripting, formats, enums, entities)
    aliases = versioning.validate_aliases(
        errors,
        MANUAL,
        scripting,
        tombstones,
        base.get("aliases") if base else None,
    )
    changes = versioning.validate_changes(
        errors,
        MANUAL,
        registry,
        current,
        scripting,
        formats,
        tombstones,
        base.get("changes") if base else None,
        base_registry,
        enums=enums,
        entities=entities,
    )
    history = versioning.validate_history(errors, registry, changes, tombstones)
    validate_required_omission_targets(
        errors,
        current,
        omission_claims,
        versioning.omission_targets(changes),
    )
    catalog_validation.validate_relations(
        errors, MANUAL, current, scripting, formats, tombstones, enums, entities)

    delta = None
    scripting_delta = None
    command_delta = None
    enum_delta = None
    if base and base.get("keys") is not None:
        base_keys = base["keys"]
        delta = classify_key_deltas(current, base_keys)
        validate_required_omissions(
            errors, current, omission_claims, delta["added"] | delta["changed"])

        base_scripting = base.get("scripting")
        if base_scripting is not None:
            scripting_delta = classify_scripting_deltas(scripting, base_scripting)
        else:
            scripting_delta = {
                plural: {
                    "added": set(), "changed": set(), "removed": set(), "shifted": {}
                }
                for plural in SCRIPTING_TABLES
            }
        # Before the August 27, 2026 public launch, command identity lives in
        # the id field and routes may change freely. Every route present at
        # launch becomes stable; see manual/MAINTAINING.md.
        base_commands = base.get("commands")
        if base_commands is not None:
            command_delta = classify_command_deltas(commands, base_commands)
        if "enum_signatures" in base:
            enum_delta = classify_enum_deltas(
                enums, base.get("enums") or {}, base.get("enum_signatures") or {})

        versioning.validate_branch_lifecycle(
            errors,
            current,
            base_keys,
            scripting,
            base_scripting or scripting,
            formats,
            formats if base.get("formats") is None else base["formats"],
            changes,
            tombstones,
            delta,
            scripting_delta,
            enum_delta,
            base.get("enums") or {},
            command_delta,
            base_commands,
        )

    validate_routes(errors)
    return errors, {
        "keys": current,
        "internals": internals,
        "enums": enums,
        "scripting": scripting,
        "formats": formats,
        "commands": commands,
        "entities": entities,
        "releases": registry,
        "changes": changes,
        "history": history,
        "tombstones": tombstones,
        "aliases": aliases,
        "delta": delta,
        "scripting_delta": scripting_delta,
        "enum_delta": enum_delta,
        "command_delta": command_delta,
    }

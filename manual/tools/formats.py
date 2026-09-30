"""Authored format catalog loading, validation, and scaffold defaults."""

from pathlib import Path
import re

import yaml

import schema_validation


MANUAL = Path(__file__).resolve().parents[1]
LEGACY_FORMAT_ROUTES = {
    "teamtypes": "/mapping/team-types/",
    "taskforces": "/mapping/task-forces/",
    "scripts": "/mapping/scripts/",
    "ai_triggers": "/mapping/ai-triggers/",
}
FORMAT_KINDS = {"syntax", "file", "registry", "record", "binary"}
BINARY_ROLES = {"archive", "image", "model", "audio", "video", "persistence"}
_FRONTMATTER = re.compile(r"^---\r?\n([\s\S]*?)\r?\n---")


def _frontmatter_text(source, context):
    match = _FRONTMATTER.match(source)
    if not match:
        raise ValueError(f"{context}: missing YAML frontmatter")
    data = yaml.safe_load(match.group(1)) or {}
    if not isinstance(data, dict):
        raise ValueError(f"{context}: frontmatter must be a mapping")
    return data


def format_route(record, slug):
    """Return the canonical public route for an authored format."""
    route = record.get("route")
    if not route:
        return f"/formats/{slug}/"
    expected = LEGACY_FORMAT_ROUTES.get(record.get("format_id"))
    if expected is None:
        raise ValueError(
            "route override is reserved for the four migrated AI format records")
    if route != expected:
        raise ValueError(
            f"route for {record.get('format_id')!r} must remain {expected!r}")
    return route


def parse_catalog(documents):
    """Parse ``(path, Markdown source)`` pairs into a catalog keyed by format ID.

    This pure boundary is also used for Git-revision snapshots. Paths may be
    absolute or repository-relative; only their filename stems affect routes.
    """
    records = {}
    routes = {}
    for path, source in documents:
        candidate = Path(path)
        data = _frontmatter_text(source, str(candidate))
        format_id = data.get("format_id")
        if not isinstance(format_id, str) or not format_id:
            continue
        if format_id in records:
            raise ValueError(f"{candidate}: duplicate format ID {format_id!r}")
        normalized = dict(data)
        normalized.setdefault("related", [])
        normalized.setdefault("key_scopes", [])
        if normalized.get("kind") == "binary":
            normalized.setdefault("companion_formats", [])
        normalized["route"] = format_route(normalized, candidate.stem)
        normalized["_slug"] = candidate.stem
        owner = routes.get(normalized["route"])
        if owner:
            raise ValueError(
                f"{candidate}: route {normalized['route']} is already owned by {owner}")
        routes[normalized["route"]] = format_id
        records[format_id] = normalized
    return records


def load_formats(manual=MANUAL):
    """Load the active authored Format catalog keyed by stable ``format_id``."""
    folder = Path(manual) / "content" / "formats"
    documents = (
        (path, path.read_text(encoding="utf-8"))
        for path in sorted(folder.glob("*.md"))
    )
    return parse_catalog(documents)


def _selector_matches(left, right):
    return isinstance(left, dict) and left == right


def _query_matches(scope, query):
    return (
        (not query.get("file") or scope.get("file") == query["file"])
        and (not query.get("section")
             or _selector_matches(scope.get("section"), query["section"]))
        and (not query.get("applies_to")
             or query["applies_to"] in scope.get("applies_to", []))
    )


def _contains_todo(value):
    if isinstance(value, str):
        return value.startswith("TODO:")
    if isinstance(value, dict):
        return any(_contains_todo(item) for item in value.values())
    if isinstance(value, list):
        return any(_contains_todo(item) for item in value)
    return False


def validate_formats(errors, keys=None, manual=MANUAL):
    """Validate authored formats and return their normalized lifecycle catalog."""
    manual = Path(manual)
    folder = manual / "content" / "formats"
    records = {}
    routes = {}
    source_documents = []

    for path in sorted(folder.glob("*.md")):
        label = str(path.relative_to(manual))
        source = path.read_text(encoding="utf-8")
        try:
            data = _frontmatter_text(source, label)
        except (OSError, ValueError, yaml.YAMLError) as error:
            errors.append(str(error))
            continue
        errors.extend(schema_validation.errors_for(
            data, "authored-format.schema.json", label))
        if _contains_todo(data):
            errors.append(
                f"{label}: replace all TODO placeholders before publishing this format")
        format_id = data.get("format_id")
        if not isinstance(format_id, str) or not format_id:
            continue
        if format_id in records:
            errors.append(f"{label}: duplicate format ID {format_id!r}")
            continue

        try:
            route = format_route(data, path.stem)
        except ValueError as error:
            errors.append(f"{label}: {error}")
            route = f"/formats/{path.stem}/"
        route_tail = next((part for part in reversed(route.split("/")) if part), "")
        if route_tail != path.stem:
            errors.append(
                f"{label}: filename must be {route_tail}.md for canonical route {route}")
        if route in routes:
            errors.append(
                f"{label}: route {route} is already owned by {routes[route]}")
        else:
            routes[route] = format_id

        normalized = dict(data)
        normalized.setdefault("related", [])
        normalized.setdefault("key_scopes", [])
        if normalized.get("kind") == "binary":
            normalized.setdefault("companion_formats", [])
        normalized["route"] = route
        normalized["_slug"] = path.stem
        records[format_id] = normalized
        source_documents.append((path, label, normalized))

    for path, label, record in source_documents:
        for source_file in record.get("source_files", []):
            if not isinstance(source_file, str):
                continue
            candidate = Path(source_file)
            if candidate.is_absolute() or ".." in candidate.parts:
                errors.append(f"{label}: invalid source path {source_file!r}")
            elif not (manual.parent / candidate).is_file():
                errors.append(f"{label}: source path does not exist: {source_file}")

        fields = record.get("fields", [])
        positions = [field.get("position") for field in fields if isinstance(field, dict)]
        if positions and positions != list(range(1, len(positions) + 1)):
            errors.append(
                f"{label}: record fields must use ordered consecutive positions starting at 1")

        registrations = record.get("registrations", [])
        registration_sections = [
            item.get("section") for item in registrations if isinstance(item, dict)
        ]
        if len(registration_sections) != len(set(registration_sections)):
            errors.append(f"{label}: duplicate registration section")

        for companion in record.get("companion_formats", []):
            if companion == record.get("format_id"):
                errors.append(f"{label}: a format cannot be its own companion")
            elif companion not in records:
                errors.append(f"{label}: unknown companion format {companion!r}")

        if keys is not None:
            scopes = [
                scope
                for entry in keys.values() if isinstance(entry, dict)
                for scope in entry.get("scopes", []) if isinstance(scope, dict)
            ]
            for position, query in enumerate(record.get("key_scopes", []), start=1):
                if isinstance(query, dict) and not any(
                        _query_matches(scope, query) for scope in scopes):
                    errors.append(
                        f"{label}: key_scopes entry {position} matches no generated scope")

    return records


def scaffold_frontmatter(format_id, kind):
    """Return minimal frontmatter for ``scaffold format``.

    TODO values intentionally keep validation/action-required output active until
    the programmer supplies source-backed facts.
    """
    if kind not in FORMAT_KINDS:
        raise ValueError(
            f"unknown format kind {kind!r}; expected one of {', '.join(sorted(FORMAT_KINDS))}")
    result = {
        "format_id": format_id,
        "title": "TODO: replace with the display title",
        "summary": "TODO: replace with one literal sentence",
        "kind": kind,
        "source_files": ["TODO: replace with a repository-relative source path"],
    }
    if kind == "syntax":
        result["applies_to"] = ["TODO: replace with the affected inputs"]
    elif kind == "file":
        result["filenames"] = ["TODO: replace with the accepted filename"]
    elif kind == "registry":
        result["files"] = ["TODO: replace with the containing file"]
        result["registrations"] = [{
            "section": "TODO: replace with the registration section",
            "id_from": "value",
            "entry_section": "TODO: replace with the definition section",
        }]
    elif kind == "record":
        result["files"] = ["TODO: replace with the containing file"]
        result["section"] = "TODO: replace with the containing section"
        result["syntax"] = "TODO: replace with the record syntax"
        result["fields"] = [{
            "position": 1,
            "label": "TODO: replace with the field label",
            "value": "TODO: replace with the accepted value",
            "required": True,
        }]
    else:
        result["extensions"] = [".TODO"]
        result["role"] = "TODO: choose archive, image, model, audio, video, or persistence"
    return result

"""Shared JSON Schema validation for generated and authored manual records."""

from functools import lru_cache
import json
from pathlib import Path

from jsonschema import Draft202012Validator


SCHEMA_DIRECTORY = Path(__file__).resolve().parents[1] / "schema"


@lru_cache(maxsize=None)
def load_schema(name):
    path = SCHEMA_DIRECTORY / name
    with path.open(encoding="utf-8") as stream:
        schema = json.load(stream)
    Draft202012Validator.check_schema(schema)
    return schema


@lru_cache(maxsize=None)
def validator(name):
    return Draft202012Validator(load_schema(name))


def _location(error):
    parts = []
    for part in error.absolute_path:
        if isinstance(part, int):
            parts.append(f"[{part}]")
        elif parts:
            parts.append(f".{part}")
        else:
            parts.append(str(part))
    return "".join(parts) or "document"


def errors_for(instance, schema_name, context):
    """Return concise, stable diagnostics instead of raw jsonschema traces."""

    failures = sorted(
        validator(schema_name).iter_errors(instance),
        key=lambda error: (tuple(str(part) for part in error.absolute_path), error.message),
    )
    return [f"{context}: {_location(error)}: {error.message}" for error in failures]

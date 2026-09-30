"""Read-only drift checks for committer-authored enum reference pages."""

from dataclasses import dataclass
from pathlib import Path
import re

import yaml


@dataclass(frozen=True)
class Adapter:
    enum_id: str
    header: str
    enum_name: str
    representation: str
    exclude: frozenset[str]
    token_source: tuple | None = None
    include_from_tokens: bool = False
    extra_sources: tuple[str, ...] = ()

    @property
    def source_files(self):
        result = [self.header, *self.extra_sources]
        if self.token_source and self.token_source[0] != "literal":
            result.append(self.token_source[1])
        return tuple(dict.fromkeys(result))


def adapter(enum_id, header, representation, *, enum_name=None, exclude=(),
            token_source=None, include_from_tokens=False, extra_sources=()):
    return Adapter(
        enum_id, header, enum_name or enum_id, representation,
        frozenset(exclude), token_source, include_from_tokens, tuple(extra_sources))


ADAPTERS = {
    row.enum_id: row for row in (
        adapter("ActionType", "code/action.hh", "token", exclude=("ACTION_COUNT",),
                token_source=("array", "code/ccini.cpp", "ActionName")),
        adapter("ArmorType", "code/armor.hh", "token",
                exclude=("ARMOR_COUNT", "ARMOR_FIRST"),
                token_source=("array", "code/const.cpp", "ArmorName")),
        adapter("BSizeType", "code/bsize.hh", "token",
                exclude=("BSIZE_NONE", "BSIZE_COUNT", "BSIZE_FIRST"),
                token_source=("pairs", "code/ccini.cpp", "_foundations"),
                include_from_tokens=True),
        adapter("CategoryType", "code/category.hh", "token",
                exclude=("CATEGORY_NONE", "CATEGORY_COUNT", "CATEGORY_FIRST"),
                token_source=("category", "code/category.cpp", "_categories")),
        adapter("CrateType", "code/crate.hh", "token",
                exclude=("CRATE_COUNT", "CRATE_FIRST"),
                token_source=("array", "code/const.cpp", "CrateNames")),
        adapter("LandType", "code/land.hh", "token",
                exclude=("LAND_NONE", "LAND_COUNT", "LAND_FIRST"),
                token_source=("array", "code/const.cpp", "LandName")),
        adapter("MZoneType", "code/mzone.hh", "token",
                exclude=("MZONE_NONE", "MZONE_COUNT", "MZONE_FIRST"),
                token_source=("array", "code/ccini.cpp", "_mzones")),
        adapter("PipEnum", "code/pip.hh", "token",
                exclude=("PIP_NONE", "PIP_COUNT"),
                token_source=("pairs", "code/ccini.cpp", "_pips"),
                include_from_tokens=True),
        adapter("PipScaleType", "code/pip.hh", "token",
                exclude=("PIPSCALE_NONE", "PIPSCALE_COUNT"),
                token_source=("pairs", "code/ccini.cpp", "_pipscales"),
                include_from_tokens=True),
        adapter("RTTIType", "code/rtti.hh", "token", exclude=("RTTI_COUNT",),
                token_source=("pairs", "code/_rtti.cpp", "RTTIs")),
        adapter("SourceType", "code/source.hh", "token",
                exclude=("SOURCE_NONE", "SOURCE_COUNT", "SOURCE_FIRST"),
                token_source=("array", "code/_source.cpp", "SourceName")),
        adapter("SpeedType", "code/speed.hh", "token",
                exclude=("SPEED_NONE", "SPEED_COUNT", "SPEED_FIRST"),
                token_source=("array", "code/const.cpp", "SpeedName")),
        adapter("LightBehaviorType", "code/blight.hh", "integer",
                exclude=("LIGHT_BEHAVIOR_COUNT", "LIGHT_BEHAVIOR_FIRST")),
        adapter("MeteorShowerType", "code/meteor.hh", "integer",
                exclude=("SHOWER_NONE", "SHOWER_COUNT", "SHOWER_FIRST")),
        adapter("MissionType", "code/mission.hh", "integer",
                exclude=("MISSION_NONE", "MISSION_COUNT", "MISSION_FIRST"),
                extra_sources=("code/_mission.cpp",)),
        adapter("QuarryType", "code/quarry.hh", "integer",
                exclude=("QUARRY_COUNT", "QUARRY_FIRST")),
        adapter("RadarEventType", "code/revent.hh", "integer",
                exclude=("RADAREVENT_NONE", "RADAREVENT_COUNT", "RADAREVENT_FIRST")),
        adapter("ScrollSpeedType", "code/scrspeed.hh", "integer",
                exclude=("SCROLL_SPEED_COUNT",)),
        adapter("TargetPropertyType", "code/target.hh", "integer",
                exclude=("TPROPERTY_COUNT",)),
        adapter("TalkType", "code/talk.hh", "integer"),
    )
}


DYNAMIC_PARAMETER_BINDINGS = {
    "house", "theme", "sound", "movie", "weapon", "animation",
    "aircraft-type", "building-type", "infantry-type", "particle-system",
    "team", "tag", "trigger", "script", "unit-type",
    "superweapon", "meteor-size",
}
DYNAMIC_KEY_BINDINGS = {
    "HouseType", "Side", "SuperWeaponType", "list of AnimTypes",
    "list of BuildingTypes", "list of HouseTypes",
    "list of ParticleSystemTypes", "list of VoxelAnimTypes",
    "list of sounds", "movie", "sound", "themetype", "technotype list",
    "typelist",
}


def is_dynamic_binding(field, value):
    catalog = (
        DYNAMIC_KEY_BINDINGS
        if field == "key_value_types"
        else DYNAMIC_PARAMETER_BINDINGS
    )
    return value in catalog


def frontmatter(path):
    source = path.read_text(encoding="utf-8")
    match = re.match(r"^---\r?\n([\s\S]*?)\r?\n---", source)
    if not match:
        raise ValueError(f"{path}: missing YAML frontmatter")
    return yaml.safe_load(match.group(1)) or {}


def strip_comments(source):
    source = re.sub(r"/\*[\s\S]*?\*/", "", source)
    return re.sub(r"//.*", "", source)


def parse_enum(source, enum_name):
    clean = strip_comments(source)
    match = re.search(rf"\benum\s+{re.escape(enum_name)}\s*\{{([\s\S]*?)\}}\s*;", clean)
    if not match:
        raise ValueError(f"enum {enum_name} was not found")
    values = []
    known = {}
    current = -1
    for raw in match.group(1).split(","):
        item = raw.strip()
        if not item:
            continue
        if "=" in item:
            name, expression = (part.strip() for part in item.split("=", 1))
            if re.fullmatch(r"-?(?:0x[0-9a-fA-F]+|[0-9]+)", expression):
                current = int(expression, 0)
            elif expression in known:
                current = known[expression]
            else:
                raise ValueError(f"{enum_name}.{name}: unsupported value expression {expression!r}")
        else:
            name = item
            current += 1
        if not re.fullmatch(r"[A-Z][A-Z0-9_]*", name):
            raise ValueError(f"{enum_name}: invalid constant declaration {name!r}")
        known[name] = current
        values.append((name, current))
    return values


def initializer(source, symbol):
    match = re.search(
        rf"\b{re.escape(symbol)}\b\s*(?:\[[^\]]*\])?\s*=\s*\{{([\s\S]*?)\}}\s*;",
        strip_comments(source),
    )
    if not match:
        raise ValueError(f"initializer {symbol} was not found")
    return match.group(1)


def token_rows(adapter_row, reader):
    source = adapter_row.token_source
    if not source:
        return None
    kind = source[0]
    if kind == "literal":
        return [(None, token) for token in source[1]]
    body = initializer(reader(source[1]), source[2])
    if kind == "array":
        return [(None, token) for token in re.findall(r'"([^"\\]*(?:\\.[^"\\]*)*)"', body)]
    if kind == "pairs":
        return [
            (constant, token)
            for token, constant in re.findall(
                r'\{\s*"([^"\\]*(?:\\.[^"\\]*)*)"\s*,\s*([A-Z][A-Z0-9_]*)\s*\}',
                body,
            )
        ]
    if kind == "category":
        return [
            (None, token)
            for _, token in re.findall(
                r'\{\s*"([^"\\]*(?:\\.[^"\\]*)*)"\s*,\s*"([^"\\]*(?:\\.[^"\\]*)*)"\s*\}',
                body,
            )
        ]
    raise ValueError(f"unknown token adapter {kind}")


def expected_values(adapter_row, reader):
    constants = [
        (name, value)
        for name, value in parse_enum(reader(adapter_row.header), adapter_row.enum_name)
        if name not in adapter_row.exclude
    ]
    rows = token_rows(adapter_row, reader)
    if adapter_row.include_from_tokens:
        names = {constant for constant, _ in rows or [] if constant}
        constants = [item for item in constants if item[0] in names]
    if adapter_row.representation == "integer":
        return [
            {"constant": name, "value": value, "input": str(value)}
            for name, value in constants
        ]
    if rows is None:
        raise ValueError(f"{adapter_row.enum_id}: token representation needs a token adapter")
    row_constants = [constant for constant, _ in rows if constant]
    if row_constants and row_constants != [name for name, _ in constants]:
        raise ValueError(
            f"{adapter_row.enum_id}: parser token order {row_constants} does not match enum order "
            f"{[name for name, _ in constants]}")
    tokens = [token for _, token in rows]
    if len(tokens) != len(constants):
        raise ValueError(
            f"{adapter_row.enum_id}: {len(tokens)} parser tokens for {len(constants)} public constants")
    return [
        {"constant": name, "value": value, "input": tokens[index]}
        for index, (name, value) in enumerate(constants)
    ]


def signature(adapter_row, reader):
    return tuple(
        (row["constant"], row["value"], row["input"])
        for row in expected_values(adapter_row, reader)
    )


def source_paths():
    return sorted({path for row in ADAPTERS.values() for path in row.source_files})


def signatures_from_sources(sources):
    def reader(path):
        if sources.get(path) is None:
            raise FileNotFoundError(path)
        return sources[path]

    result = {}
    for enum_id, row in ADAPTERS.items():
        try:
            result[enum_id] = signature(row, reader)
        except (FileNotFoundError, ValueError):
            result[enum_id] = None
    return result


def validate_enums(errors, manual, root):
    folder = manual / "content" / "enums"
    records = {}
    slugs = {}
    enum_ids = {}
    key_bindings = {}
    parameter_bindings = {}
    for path in folder.glob("*.md"):
        context = str(path.relative_to(manual))
        try:
            data = frontmatter(path)
        except ValueError as error:
            errors.append(str(error))
            continue
        enum_id, slug = data.get("enum_id"), data.get("slug")
        if not isinstance(enum_id, str) or not enum_id:
            errors.append(f"{context}: enum_id must be a non-empty C++ enum name")
            continue
        if enum_id in enum_ids:
            errors.append(f"{context}: duplicate enum ID {enum_id}; first used by {enum_ids[enum_id]}")
        enum_ids[enum_id] = context
        if not isinstance(slug, str) or not re.fullmatch(r"[a-z0-9]+(?:-[a-z0-9]+)*", slug):
            errors.append(f"{context}: slug must be kebab-case")
        elif slug != path.stem:
            errors.append(f"{context}: filename must match immutable enum slug {slug!r}")
        elif slug in slugs:
            errors.append(f"{context}: duplicate enum route slug {slug}")
        slugs[slug] = context
        adapter_row = ADAPTERS.get(enum_id)
        if not adapter_row:
            errors.append(f"{context}: no explicit source adapter for {enum_id}")
            continue
        if data.get("representation") != adapter_row.representation:
            errors.append(
                f"{context}: representation must be {adapter_row.representation!r} for {enum_id}")
        for field in ("title", "summary"):
            if not isinstance(data.get(field), str) or not data[field].strip():
                errors.append(f"{context}: {field} must be a non-empty string")
        source_files = data.get("source_files")
        if not isinstance(source_files, list) or not source_files:
            errors.append(f"{context}: source_files must be a non-empty list")
            source_files = []
        for required in adapter_row.source_files:
            if required not in source_files:
                errors.append(f"{context}: source_files must include adapter source {required}")
        for source_file in source_files:
            if (not isinstance(source_file, str) or Path(source_file).is_absolute()
                    or ".." in Path(source_file).parts):
                errors.append(f"{context}: invalid source path {source_file!r}")
            elif not (root / source_file).is_file():
                errors.append(f"{context}: source path does not exist: {source_file}")
        bindings = data.get("bindings")
        if not isinstance(bindings, dict) or set(bindings) != {
                "key_value_types", "scripting_parameter_types"}:
            errors.append(f"{context}: bindings must contain key_value_types and scripting_parameter_types")
            bindings = {"key_value_types": [], "scripting_parameter_types": []}
        for field, registry in (
                ("key_value_types", key_bindings),
                ("scripting_parameter_types", parameter_bindings)):
            values = bindings.get(field)
            if not isinstance(values, list) or not all(
                    isinstance(value, str) and value for value in values):
                errors.append(f"{context}: {field} must be an array of non-empty strings")
                continue
            for value in values:
                if value in registry:
                    errors.append(
                        f"{context}: duplicate {field} binding {value!r}; already bound by {registry[value]}")
                registry[value] = enum_id
                if is_dynamic_binding(field, value):
                    errors.append(
                        f"{context}: dynamic identifier type {value!r} "
                        "cannot be an enum binding")
        values = data.get("values")
        if not isinstance(values, list) or not values:
            errors.append(f"{context}: values must be a non-empty ordered array")
            values = []
        authored = []
        constants_seen = set()
        for position, value in enumerate(values, start=1):
            value_context = f"{context} value {position}"
            if not isinstance(value, dict):
                errors.append(f"{value_context}: expected a mapping")
                continue
            unexpected = set(value) - {"constant", "value", "input", "meaning", "note"}
            missing = {"constant", "value", "input", "meaning"} - set(value)
            if unexpected:
                errors.append(f"{value_context}: unexpected fields {sorted(unexpected)}")
            if missing:
                errors.append(f"{value_context}: missing fields {sorted(missing)}")
            constant = value.get("constant")
            if constant in constants_seen:
                errors.append(f"{value_context}: duplicate constant {constant}")
            constants_seen.add(constant)
            if not isinstance(value.get("value"), int):
                errors.append(f"{value_context}: value must be an integer")
            if not isinstance(value.get("input"), str):
                errors.append(f"{value_context}: input must be a string")
            if not isinstance(value.get("meaning"), str) or not value.get("meaning", "").strip():
                errors.append(f"{value_context}: meaning must be a non-empty authored string")
            if "note" in value and (
                    not isinstance(value["note"], str) or not value["note"].strip()):
                errors.append(f"{value_context}: note must be a non-empty string")
            authored.append((constant, value.get("value"), value.get("input")))
        try:
            expected = signature(adapter_row, lambda name: (root / name).read_text(encoding="utf-8"))
        except (OSError, ValueError) as error:
            errors.append(f"{context}: enum source adapter failed: {error}")
            expected = ()
        if tuple(authored) != expected:
            for position in range(max(len(authored), len(expected))):
                actual = authored[position] if position < len(authored) else None
                wanted = expected[position] if position < len(expected) else None
                if actual != wanted:
                    errors.append(
                        f"{context}: enum drift at value {position + 1}: authored {actual!r}; "
                        f"source requires {wanted!r}")
        records[enum_id] = {**data, "_signature": expected}

    for enum_id in sorted(set(ADAPTERS) - set(records)):
        errors.append(
            f"content/enums: selected public domain {enum_id} is missing its authored page")
    return records
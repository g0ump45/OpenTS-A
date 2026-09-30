"""Closed public vocabulary for generated INI section selectors.

The extractor sees C++ expressions; the generated catalog exposes only the
stable concepts a programmer or site renderer needs.  Any expression that is
not classified here or by a reader-specific adapter is an extraction error.
"""

IDENTIFIER_SOURCES = (
    "object-type",
    "house",
    "difficulty",
    "campaign",
    "theme",
    "sound",
    "tile-set",
    "land-type",
    "mission",
    "multiplayer-map",
    # Retained only so branch-base catalogs that still carry it stay
    # comparable; current extraction classifies AI-base reads under "house"
    # because the base lives in the owning house's own map section.
    "base-owner-house",
)

# An Image= read either falls back to the object's own entry or has nothing to
# fall back to.  The reader decides: ObjectTypeClass::Read_INI passes the
# current GraphicName as its default and keeps it, while a reader that supplies
# an empty default wipes the name before the art reads run.
IMAGE_FALLBACKS = ("object-type", None)


class SectionSelectorError(ValueError):
    """A C++ section expression has no safe public representation."""


def literal(name):
    if not isinstance(name, str) or not name:
        raise SectionSelectorError("literal section names must be non-empty strings")
    if "[" in name or "]" in name:
        raise SectionSelectorError(
            f"literal section name {name!r} must not include brackets")
    return {"kind": "literal", "name": name}


def identifier(source):
    if source not in IDENTIFIER_SOURCES:
        raise SectionSelectorError(
            f"identifier source {source!r} is not in the public selector vocabulary")
    return {"kind": "identifier", "source": source}


def image(fallback="object-type"):
    if fallback not in IMAGE_FALLBACKS:
        raise SectionSelectorError(
            f"image fallback {fallback!r} is not in the public selector vocabulary")
    if fallback is None:
        return {"kind": "image"}
    return {"kind": "image", "fallback": fallback}


def require(value):
    """Validate and canonicalize one already-public selector object."""

    if not isinstance(value, dict):
        raise SectionSelectorError("section selector must be an object")
    kind = value.get("kind")
    if kind == "literal" and set(value) == {"kind", "name"}:
        return literal(value["name"])
    if kind == "identifier" and set(value) == {"kind", "source"}:
        return identifier(value["source"])
    if (kind == "image" and set(value) == {"kind", "fallback"}
            and value.get("fallback") == "object-type"):
        return image()
    if kind == "image" and set(value) == {"kind"}:
        return image(None)
    raise SectionSelectorError(
        "section selector must be literal{name}, identifier{source}, "
        "image{fallback: object-type}, or image{}")


def classify(expression, *, constants=None, variables=None,
             default_identifier="object-type", context=None):
    """Translate one C++ section expression to the public selector contract."""

    try:
        if isinstance(expression, dict):
            return require(expression)
        if not isinstance(expression, str):
            raise SectionSelectorError(
                f"section expression must be text, got {type(expression).__name__}")

        expression = expression.strip()
        variables = variables or {}
        constants = constants or {}
        if expression in variables:
            return require(variables[expression])
        if len(expression) >= 2 and expression[0] == expression[-1] == '"':
            return literal(expression[1:-1])
        if expression in constants:
            return literal(constants[expression])
        if expression in {"Name()", "IniName"}:
            return identifier(default_identifier)
        if expression in {"GraphicName", "Graphic_Name()"}:
            return image()
        raise SectionSelectorError(
            f"unclassified INI section expression {expression!r}; add a "
            "reader-specific section_vars adapter backed by source evidence")
    except SectionSelectorError as error:
        if context:
            raise SectionSelectorError(f"{context}: {error}") from error
        raise


_LEGACY_SELECTORS = {
    "the object's own entry": identifier("object-type"),
    "the house's own entry": identifier("house"),
    "the selected difficulty entry": identifier("difficulty"),
    "the campaign's own entry": identifier("campaign"),
    "the theme's own entry": identifier("theme"),
    "the sound's own entry": identifier("sound"),
    "the tile set's own entry": identifier("tile-set"),
    "the base owner's house entry": identifier("base-owner-house"),
    "the entry named by this object's Image=": image(),
    "the entry named by this object's Image= (defaults to the object's own name)": image(),
    # These four values escaped the old prose adapter.  They are retained only
    # for branch-base comparison; generated data validation still rejects every
    # string selector.
    "INI_NAME": literal("LEVITATION"),
    "section": identifier("tile-set"),
    "name": literal("Map"),
    "_lands[land]": identifier("land-type"),
}


def normalize_legacy(value):
    """Normalize old generated values for semantic branch comparison only."""

    if isinstance(value, dict):
        try:
            return require(value)
        except SectionSelectorError:
            return value
    if not isinstance(value, str):
        return value
    if len(value) >= 2 and value.startswith("[") and value.endswith("]"):
        try:
            return literal(value[1:-1])
        except SectionSelectorError:
            return value
    return _LEGACY_SELECTORS.get(value, value)


def normalize_scope(scope):
    """Copy a semantic scope while normalizing current and legacy selectors."""

    result = dict(scope)
    if "section" in result:
        result["section"] = normalize_legacy(result["section"])
    if isinstance(result.get("read_from"), list):
        result["read_from"] = [
            {
                **source,
                "section": normalize_legacy(source.get("section")),
            }
            if isinstance(source, dict) and "section" in source else source
            for source in result["read_from"]
        ]
    return result

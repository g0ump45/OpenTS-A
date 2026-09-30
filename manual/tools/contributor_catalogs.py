"""Scaffolds for authored catalog pages introduced by the public manual IA."""

FORMAT_KINDS = {"syntax", "file", "registry", "record", "binary"}


SYSTEM_CATEGORIES = (
    "combat-targeting",
    "units-movement",
    "buildings-economy",
    "weapons-projectiles",
    "superweapons-special",
    "ai-teams",
    "maps-scenarios",
    "interface-controls",
    "rendering-presentation",
    "audio-speech",
    "multiplayer-networking",
    "tools-diagnostics",
)
GUIDE_CATEGORIES = (
    "setup",
    "configuration",
    "files-formats",
    "compatibility-migration",
    "troubleshooting",
)
USING_CATEGORIES = (
    "getting-started",
    "configuration",
    "compatibility-migration",
    "troubleshooting",
)


def _route_id(engine, identifier):
    route = engine._slugify(identifier)
    if not route:
        raise ValueError("the authored page ID must contain a letter or number")
    return route


def _sentence_title(identifier):
    words = identifier.replace("_", " ").replace("-", " ").strip()
    return words[:1].upper() + words[1:]


def _write(engine, path, frontmatter, body):
    path.parent.mkdir(parents=True, exist_ok=True)
    return engine._write(path, frontmatter, body)


def scaffold_system(engine, identifier):
    route = _route_id(engine, identifier)
    path = engine.MANUAL / "content" / "systems" / f"{route}.md"
    _write(engine, path, {
        "title": _sentence_title(route),
        "summary": "TODO: state the runtime behavior in one literal sentence",
        "category": "TODO: choose a Features & systems category",
        "keys": [],
    }, "TODO: explain the runtime behavior and material interactions.")


def scaffold_guide(engine, identifier):
    route = _route_id(engine, identifier)
    path = engine.MANUAL / "content" / "guides" / f"{route}.md"
    _write(engine, path, {
        "title": _sentence_title(route),
        "summary": "TODO: state the procedure or failure condition in one sentence",
        "category": "TODO: choose a guide category",
        "uses_keys": [],
        "prerequisites": [],
    }, "TODO: write the smallest complete procedure or troubleshooting path.")


def scaffold_using(engine, identifier, category):
    if category not in USING_CATEGORIES:
        raise ValueError(
            "using pages require --category with one of: "
            + ", ".join(USING_CATEGORIES))
    route = _route_id(engine, identifier)
    path = engine.MANUAL / "content" / "using" / f"{route}.md"
    _write(engine, path, {
        "title": _sentence_title(route),
        "summary": "TODO: state the supported usage boundary in one sentence",
        "category": category,
        "source_files": [
            "TODO: replace with an authoritative repository-relative source path"
        ],
    }, "TODO: document only source-established setup or compatibility facts.")


def scaffold_format(engine, identifier, kind):
    import formats

    if not kind:
        raise ValueError(
            "format scaffolds require --kind with one of: "
            + ", ".join(sorted(formats.FORMAT_KINDS)))
    route = _route_id(engine, identifier)
    path = engine.MANUAL / "content" / "formats" / f"{route}.md"
    _write(engine,
        path,
        formats.scaffold_frontmatter(identifier, kind),
        "TODO: document the structure, loading rule, or compatibility gate.",
    )


def scaffold_command(engine, identifier):
    data_path = engine.DATA / "commands.yaml"
    if not data_path.is_file():
        raise ValueError("manual/data/commands.yaml is missing; run manage.py update first")
    data = engine._read_yaml(data_path) or {}
    matches = [
        row
        for table in ("registered_commands", "fixed_controls", "launch_options")
        for row in data.get(table, [])
        if isinstance(row, dict) and row.get("id") == identifier
    ]
    if not matches:
        raise ValueError(
            f"unknown generated command ID {identifier!r}; preserve exact case and run manage.py update first")
    if len(matches) != 1:
        raise ValueError(f"generated command ID {identifier!r} is ambiguous")
    route = matches[0].get("route_id")
    if not isinstance(route, str) or not route:
        raise ValueError(f"generated command ID {identifier!r} has no stable route")
    path = engine.MANUAL / "content" / "commands" / f"{route}.md"
    _write(engine,
        path,
        {"command_id": identifier},
        "TODO: explain only behavior that is not present in the generated command record.",
    )

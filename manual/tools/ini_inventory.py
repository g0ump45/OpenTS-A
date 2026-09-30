"""Token-aware inventory of typed literal INI accessor calls.

Normal ``Class::Read_INI`` implementations are discovered automatically.  The
hand-owned manifest is reserved for exceptional structural adapters, absorbed
duplicates, and reasoned non-public reads.  Source lines are diagnostic only;
classifications are stable function/key identities, never fingerprints.
"""

from dataclasses import dataclass
from pathlib import Path
import re

import yaml

import extract
import schema_validation


MANIFEST = Path(__file__).resolve().parents[1] / "data" / "ini-read-exclusions.yaml"
SOURCE_SUFFIXES = {".cpp", ".h", ".hh"}
FUNCTION_RE = re.compile(
    r"(?P<name>(?:[A-Za-z_]\w*::)*[~A-Za-z_]\w*)\s*"
    r"\([^;{}]*\)\s*(?:const\s*)?(?:noexcept\s*)?\{",
    re.M,
)
READ_INI_RE = re.compile(
    r"\b(?:bool|void|int)\s+(?P<class>[A-Za-z_]\w*)::Read_INI\s*\(")
CONTROL_NAMES = {"if", "for", "switch", "while", "catch"}


@dataclass(frozen=True)
class ReadSite:
    path: str
    line: int
    function: str
    accessor: str
    key: str
    context: str

    @property
    def source(self):
        return f"{self.path}:{self.line}"


def _matching_brace(text, opening):
    depth = 0
    index = opening
    while index < len(text):
        char = text[index]
        if char == '"':
            index += 1
            while index < len(text) and text[index] != '"':
                index += 2 if text[index] == "\\" else 1
        elif char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return index
        index += 1
    return len(text)


def function_spans(text):
    spans = []
    for match in FUNCTION_RE.finditer(text):
        name = match.group("name")
        if name in CONTROL_NAMES:
            continue
        opening = text.find("{", match.start(), match.end())
        spans.append((opening, _matching_brace(text, opening), name))
    return spans


def enclosing_function(spans, position):
    matches = [span for span in spans if span[0] <= position <= span[1]]
    return min(matches, key=lambda span: span[1] - span[0])[2] if matches else "<file-scope>"


def _string_literal(value):
    match = re.fullmatch(r'"((?:[^"\\]|\\.)*)"', value.strip(), re.S)
    return match.group(1) if match else None


def literal_key(args):
    """Return a literal entry name, excluding section-only accessor forms.

    Once the caller has stripped the INI-object arguments, every accessor
    spells the section first and the entry second, so only the second argument
    can name an entry. Taking the first literal anywhere in the list instead
    read a trailing default -- ``Get_String(section, entry, "")`` -- as though
    it were the entry name.
    """

    if len(args) < 2:
        return None
    return _string_literal(args[1])


def sites_in_text(raw, relative):
    """Return the typed literal reads in one source text."""

    text = extract.strip_comments(raw)
    spans = function_spans(text)
    lines = raw.splitlines()
    sites = []
    for match in extract.GET_CALL_RE.finditer(text):
        inner, _ = extract.match_call(text, match.end() - 1)
        if inner is None:
            continue
        args = extract.split_args(inner)
        if (match.group("recv") is None and args
                and re.fullmatch(r"[A-Za-z_]\w*", args[0])):
            args = args[1:]
        # Get_VocType_List(ini, section, ...) passes the file twice.
        if args and args[0] in extract.INI_FILES:
            args = args[1:]
        key = literal_key(args)
        if key is None or not extract.KEY_NAME_RE.fullmatch(key):
            continue
        line = raw[:match.start()].count("\n") + 1
        context = lines[line - 1].strip() if line <= len(lines) else ""
        sites.append(ReadSite(
            path=relative,
            line=line,
            function=enclosing_function(spans, match.start()),
            accessor=match.group("fn"),
            key=key,
            context=context,
        ))
    return sites


def scan_source(path, code_directory):
    return sites_in_text(
        path.read_text(encoding="latin-1"),
        "code/" + path.relative_to(code_directory).as_posix())


def discover_literal_reads(code_directory):
    root = Path(code_directory)
    sites = []
    for path in sorted(root.rglob("*")):
        if path.is_file() and path.suffix.lower() in SOURCE_SUFFIXES:
            sites.extend(scan_source(path, root))
    return sites


def load_manifest(path=MANIFEST):
    candidate = Path(path)
    with candidate.open(encoding="utf-8") as stream:
        data = yaml.safe_load(stream) or {}
    errors = schema_validation.errors_for(
        data, "ini-read-exclusions.schema.json", str(candidate))
    if errors:
        raise ValueError("\n".join(errors))
    return data


def discover_read_ini_readers(code_directory):
    root = Path(code_directory)
    readers = set()
    for path in sorted(root.rglob("*.cpp")):
        source = extract.strip_comments(path.read_text(encoding="latin-1"))
        relative = "code/" + path.relative_to(root).as_posix()
        for match in READ_INI_RE.finditer(source):
            readers.add((relative, f"{match.group('class')}::Read_INI"))
    return readers


def discover_read_ini_units(code_directory, manifest, configured=()):
    """Return newly discovered ordinary ``Class::Read_INI`` units."""

    configured = set(configured)
    excluded = {
        (row["path"], row["function"])
        for row in manifest.get("reader_exclusions", [])
    }
    units = []
    root = Path(code_directory)
    for path in sorted(root.rglob("*.cpp")):
        source = extract.strip_comments(path.read_text(encoding="latin-1"))
        source_path = path.relative_to(root).as_posix()
        relative = "code/" + source_path
        for match in READ_INI_RE.finditer(source):
            cls = match.group("class")
            identity = (source_path, cls)
            function = f"{cls}::Read_INI"
            if identity in configured or (relative, function) in excluded:
                continue
            units.append(identity)
    return units


def extracted_sites(records_by_class):
    result = set()
    for records in records_by_class.values():
        for record in records:
            result.add((f"code/{record['src']}", record["line"], record["key"]))
    return result


def _rule_matches(rule, site):
    if rule["path"] != site.path or rule["function"] != site.function:
        return False
    if site.key not in rule["keys"]:
        return False
    if rule.get("accessors") and site.accessor not in rule["accessors"]:
        return False
    return True


def suppressed_sites(manifest, sites):
    """Return the site triples an ``excluded`` rule keeps out of the catalog.

    A site inside a reader the catalog already owns is extracted before any
    classification runs, so an exclusion naming it would otherwise be
    unreachable and would then report itself stale. Resolving the rules against
    discovered sites lets one manifest govern both cases, and a rule that stops
    matching a real site is still reported.
    """

    rules = [
        rule for rule in manifest.get("site_exclusions", [])
        if rule["classification"] == "excluded"
    ]
    return {
        (site.path, site.line, site.key)
        for site in sites
        for rule in rules
        if _rule_matches(rule, site)
    }


def drop_suppressed(records_by_class, manifest, sites):
    """Return the records with every ``excluded`` read removed.

    Assembly and classification must agree, so run this before
    :func:`validate_inventory`: the sites it removes are then reported as
    unmatched and matched against the same rules that removed them.
    """

    suppressed = suppressed_sites(manifest, sites)
    if not suppressed:
        return records_by_class
    return {
        unit: [
            record for record in records
            if (f"code/{record['src']}", record["line"], record["key"])
            not in suppressed
        ]
        for unit, records in records_by_class.items()
    }


def validate_inventory(records_by_class, manifest, code_directory, sites=None):
    if sites is None:
        sites = discover_literal_reads(code_directory)
    extracted = extracted_sites(records_by_class)
    unmatched = [
        site for site in sites
        if (site.path, site.line, site.key) not in extracted
    ]
    rules = manifest.get("site_exclusions", [])
    hits = [set() for _ in rules]
    unclassified = []
    classifications = {"adapter": 0, "duplicate": 0, "excluded": 0}
    for site in unmatched:
        matching = [
            index for index, rule in enumerate(rules)
            if _rule_matches(rule, site)
        ]
        if len(matching) != 1:
            unclassified.append((site, len(matching)))
            continue
        index = matching[0]
        hits[index].add(site.key)
        classifications[rules[index]["classification"]] += 1

    errors = []
    for site, count in unclassified:
        detail = "matches overlapping rules" if count else "has no classification"
        errors.append(
            f"{site.source} {site.function}: {site.accessor}(..., {site.key!r}, ...) "
            f"{detail}. Source: {site.context!r}. Extract it normally, add a "
            "dynamic-reader adapter, absorb a proven duplicate, or add one "
            "reasoned function/key exclusion to manual/data/ini-read-exclusions.yaml")
    for index, seen_keys in enumerate(hits):
        rule = rules[index]
        missing_keys = set(rule["keys"]) - seen_keys
        if missing_keys:
            errors.append(
                "manual/data/ini-read-exclusions.yaml: stale site classification "
                f"{rule['path']} {rule['function']} keys={sorted(missing_keys)}")

    discovered_readers = discover_read_ini_readers(code_directory)
    for rule in manifest.get("reader_exclusions", []):
        identity = (rule["path"], rule["function"])
        if identity not in discovered_readers:
            errors.append(
                "manual/data/ini-read-exclusions.yaml: stale reader exclusion "
                f"{rule['path']} {rule['function']}")

    summary = {
        "sites": len(sites),
        "extracted": len(sites) - len(unmatched),
        "unclassified": len(unclassified),
        **classifications,
    }
    return errors, summary

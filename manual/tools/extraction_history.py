"""Distinguish extractor coverage corrections from genuine engine changes."""

from collections import Counter
import json
from pathlib import Path
import re

import section_selectors


SEMANTIC_SCOPE_FIELDS = (
    "applies_to", "file", "section", "value_type", "level", "note",
    "precedence", "read_from",
)
SOURCE_RE = re.compile(r"(code/[^:\s]+)(?::[1-9][0-9]*)?")
TYPED_ACCESSOR_RE = re.compile(r"\bT?Get_[A-Za-z_]\w*\s*(?:<[^>]+>)?\s*\(")


def _normalize(text):
    return re.sub(r"\s+", " ", text or "").strip()


def _statement_at(source, line_number):
    """Return the complete typed accessor statement at a provenance line."""

    lines = source.splitlines()
    start = max(0, line_number - 1)
    selected = []
    for line in lines[start:start + 32]:
        selected.append(line)
        joined = "\n".join(selected)
        if ";" in line and TYPED_ACCESSOR_RE.search(joined):
            statement = _normalize(joined[:joined.find(";") + 1])
            return statement if TYPED_ACCESSOR_RE.search(statement) else ""
    return ""


def _scan(source, path):
    # Deferred: the inventory pulls in yaml and the extractor, and `doctor`
    # must start without them.
    import ini_inventory

    return ini_inventory.sites_in_text(source, path)


def _read_lines(source, sites, key, member):
    """Return the lines of the typed reads that can produce this key."""

    lines = sorted({site.line for site in sites if site.key == key})
    if lines or not member:
        return lines
    # A read that formats its entry name, such as "BurstDelay%d", names no
    # literal key. Fall back to the reads that fill the recorded member.
    pattern = re.compile(r"\b%s\b" % re.escape(member))
    return [
        number for number, text in enumerate(source.splitlines(), start=1)
        if pattern.search(text) and TYPED_ACCESSOR_RE.search(text)
    ]


def _reads(source, sites, key, member):
    statements = {
        _statement_at(source, line)
        for line in _read_lines(source, sites, key, member)
    }
    statements.discard("")
    return statements


def _semantic_scope(scope):
    normalized = {
        field: scope[field]
        for field in SEMANTIC_SCOPE_FIELDS
        if field in scope
    }
    if "level" not in normalized:
        declared = (scope.get("_provenance") or {}).get("declared_in")
        if declared:
            normalized["level"] = declared
    normalized = section_selectors.normalize_scope(normalized)
    return json.dumps(normalized, sort_keys=True, separators=(",", ":"))


def _only(scopes, other_scopes):
    """Multiset semantic difference preserving the source-bearing scopes."""

    remaining = Counter(_semantic_scope(scope) for scope in other_scopes)
    result = []
    for scope in scopes:
        signature = _semantic_scope(scope)
        if remaining[signature]:
            remaining[signature] -= 1
        else:
            result.append(scope)
    return result


def historical_corrections(current_keys, base_keys, root, load_base_source):
    """Return catalog changes fully explained by pre-existing typed reads.

    New keys qualify only when every typed read naming the key in the cited
    file already exists in the selected base source.  Semantically changed keys
    use a symmetric test: every current-only scope must predate the branch and
    every base-only scope's reads must still exist in the working source.  This
    suppresses extractor coverage/reclassification churn without hiding a
    genuine added, removed, or changed accessor call.

    Provenance cites a file rather than a position, so the reads are relocated
    by scanning that file with the shared inventory scanner and matched on
    statement text, which a commit that only moves code cannot disturb.
    """

    root = Path(root)
    current_sources = {}
    base_sources = {}
    current_sites = {}
    base_sites = {}
    normalized_current = {}
    normalized_base = {}

    def sources(path):
        if path not in current_sources:
            candidate = root / path
            current_sources[path] = (
                candidate.read_text(encoding="latin-1")
                if candidate.is_file() else "")
            base_sources[path] = load_base_source(path) or ""
            current_sites[path] = _scan(current_sources[path], path)
            base_sites[path] = _scan(base_sources[path], path)
            normalized_current[path] = _normalize(current_sources[path])
            normalized_base[path] = _normalize(base_sources[path])
        return current_sources[path], base_sources[path]

    def _cited(scope):
        match = SOURCE_RE.fullmatch(
            str((scope.get("_provenance") or {}).get("source", "")))
        if not match:
            return None, None
        return match.group(1), (scope.get("_provenance") or {}).get("member")

    def current_scope_predates(key, scope):
        path, member = _cited(scope)
        if not path:
            return False
        current_source, _ = sources(path)
        statements = _reads(current_source, current_sites[path], key, member)
        return bool(statements) and all(
            statement in normalized_base[path] for statement in statements)

    def base_scope_remains(key, scope):
        path, member = _cited(scope)
        if not path:
            return False
        _, base_source = sources(path)
        statements = _reads(base_source, base_sites[path], key, member)
        return bool(statements) and all(
            statement in normalized_current[path] for statement in statements)

    corrections = set()
    for key in set(current_keys) - set(base_keys):
        scopes = current_keys[key].get("scopes", [])
        if scopes and all(current_scope_predates(key, scope) for scope in scopes):
            corrections.add(key)

    for key in set(current_keys) & set(base_keys):
        current_scopes = current_keys[key].get("scopes", [])
        base_scopes = base_keys[key].get("scopes", [])
        current_only = _only(current_scopes, base_scopes)
        base_only = _only(base_scopes, current_scopes)
        if not current_only and not base_only:
            continue
        if (all(current_scope_predates(key, scope) for scope in current_only)
                and all(base_scope_remains(key, scope) for scope in base_only)):
            corrections.add(key)
    return corrections

"""A key's scopes must not depend on the order its readers are visited in.

Two related readers can make the same read for the same concrete type:
BulletTypeClass::Read_INI reads Image after ObjectTypeClass::Read_INI has
already read it. The coalescer folds that pair into one scope. Folding on
arrival order made the surviving declaration -- and whether the type stayed
inside its family's scope at all -- depend on where each reader sat in the unit
lists, so adding one unit could silently split or merge a published scope.
"""

import json
from pathlib import Path
import sys
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import extract
import extract_engine
import ini_inventory
import validate_manual


TREE = {"DerivedTypeClass": "BaseTypeClass"}


def read_record(declared_in, line, source):
    return {
        "key": "Image",
        "receiver": "ini",
        "suffix": "String",
        "section_expr": '"General"',
        "default_expr": None,
        "local_lhs": False,
        "member": "GraphicName",
        "value_type": "string",
        "declared_in": declared_in,
        "guard": None,
        "line": line,
        "src": source,
        "group": "BulletType",
        "file_hint": "rules.ini",
    }


def scopes_for(units):
    keys = extract_engine.build(
        dict(units), {name: {} for name, _ in units}, TREE, loader_contexts=[])
    return keys["Image"]["scopes"]


BASE_UNIT = ("BaseTypeClass", [read_record("BaseTypeClass", 662, "objtype.cpp")])
DERIVED_UNIT = (
    "DerivedTypeClass",
    [read_record("DerivedTypeClass", 195, "bullettype.cpp")],
)


class CoalescingOrderTests(unittest.TestCase):
    def test_a_repeated_read_folds_to_one_scope_in_either_order(self):
        forward = scopes_for([BASE_UNIT, DERIVED_UNIT])
        backward = scopes_for([DERIVED_UNIT, BASE_UNIT])
        self.assertEqual(len(forward), 1)
        self.assertEqual(forward, backward)

    def test_the_widest_declaration_owns_the_folded_read(self):
        for units in ([BASE_UNIT, DERIVED_UNIT], [DERIVED_UNIT, BASE_UNIT]):
            with self.subTest(order=[name for name, _ in units]):
                scope = scopes_for(units)[0]
                self.assertEqual(
                    scope["_provenance"]["declared_in"], "BaseTypeClass")
                self.assertEqual(
                    scope["_provenance"]["source"], "code/objtype.cpp")

    def test_unrelated_readers_still_keep_separate_scopes(self):
        stranger = (
            "OtherTypeClass",
            [dict(read_record("BaseTypeClass", 40, "other.cpp"),
                  declared_in="OtherTypeClass")],
        )
        self.assertEqual(len(scopes_for([BASE_UNIT, stranger])), 2)


class TrackedCatalogCoalescingTests(unittest.TestCase):
    """Re-extract with every unit list reversed and pin the published scopes."""

    @classmethod
    def setUpClass(cls):
        cls.tracked = validate_manual.read_yaml(
            TOOLS.parent / "data" / "ini-keys.yaml")
        units, global_units = list(extract.UNITS), list(extract.GLOBAL_UNITS)
        extract.UNITS = list(reversed(units))
        extract.GLOBAL_UNITS = list(reversed(global_units))
        try:
            cls.reordered = extract._extract_all(
                ini_inventory.load_manifest())[0]
        finally:
            extract.UNITS, extract.GLOBAL_UNITS = units, global_units

    @staticmethod
    def signatures(entry):
        return sorted(
            json.dumps(scope, sort_keys=True, default=str)
            for scope in entry["scopes"]
        )

    def test_every_key_keeps_its_scope_count(self):
        self.assertEqual(
            {name: len(entry["scopes"])
             for name, entry in self.tracked.items()},
            {name: len(entry["scopes"])
             for name, entry in self.reordered.items()},
        )

    def test_every_scope_keeps_its_published_content(self):
        for name, entry in self.tracked.items():
            with self.subTest(key=name):
                self.assertEqual(
                    self.signatures(entry),
                    self.signatures(self.reordered[name]))


if __name__ == "__main__":
    unittest.main()

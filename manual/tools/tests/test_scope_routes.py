"""Suffixed scope routes must come from recorded content, not extraction order."""

from pathlib import Path
import sys
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import extract
import extract_engine
import validate_manual


def read_record(key, declared_in, member, line, source, **overrides):
    record = {
        "key": key,
        "receiver": "ConfigINI",
        "suffix": "Int",
        "section_expr": '"Video"',
        "default_expr": None,
        "local_lhs": False,
        "member": member,
        "value_type": "integer",
        "declared_in": declared_in,
        "guard": None,
        "line": line,
        "src": source,
        "group": "client settings",
        "file_hint": "sun.ini",
    }
    record.update(overrides)
    return record


def routes_for(units):
    keys = extract_engine.build(
        {name: records for name, records in units},
        {name: {} for name, _ in units},
        {},
        loader_contexts=[],
    )
    return {
        name: validate_manual.scope_route_ids(entry)
        + [scope["_provenance"]["declared_in"] for scope in entry["scopes"]]
        for name, entry in keys.items()
    }


class ScopeRouteOrderTests(unittest.TestCase):
    def test_route_ids_ignore_the_order_units_are_extracted_in(self):
        options = ("OptionsClass", [
            read_record("ScreenWidth", "OptionsClass", "ScreenWidth", 349, "options.cpp"),
        ])
        startup = ("Startup", [
            read_record("ScreenWidth", "Startup", "Options", 766, "startup.cpp"),
        ])
        forward = routes_for([options, startup])
        reversed_units = routes_for([startup, options])
        self.assertEqual(
            forward["ScreenWidth"],
            ["client-settings", "client-settings-2", "OptionsClass", "Startup"])
        self.assertEqual(forward, reversed_units)

    def test_value_type_orders_two_reads_of_one_spelling(self):
        house = ("ScenarioClass", [
            read_record(
                "Player", "ScenarioClass", "house", 3442, "scenario.cpp",
                value_type="HouseType", group="scenarios", file_hint="map file"),
            read_record(
                "Player", "ScenarioClass", None, 1749, "scenario.cpp",
                value_type="string", group="scenarios", file_hint="map file"),
        ])
        self.assertEqual(
            routes_for([house])["Player"],
            ["scenarios", "scenarios-2", "ScenarioClass", "ScenarioClass"])

    def test_a_named_destination_orders_ahead_of_an_anonymous_read(self):
        scenario = ("ScenarioClass", [
            read_record(
                "Official", "ScenarioClass", None, 2057, "scenario.cpp",
                value_type="boolean", group="scenarios", file_hint="map file"),
            read_record(
                "Official", "ScenarioClass", "official", 1704, "scenario.cpp",
                value_type="boolean", group="scenarios", file_hint="map file"),
        ])
        self.assertEqual(
            routes_for([scenario])["Official"][:2], ["scenarios", "scenarios-2"])
        self.assertEqual(
            [
                scope["_provenance"]["member"]
                for scope in extract_engine.build(
                    {scenario[0]: scenario[1]}, {scenario[0]: {}}, {},
                    loader_contexts=[])["Official"]["scopes"]
            ],
            ["official", None])

    def test_indistinguishable_scopes_fail_instead_of_taking_a_route_by_position(self):
        scope = {
            "applies_to": ["client settings"],
            "file": "sun.ini",
            "section": {"kind": "literal", "name": "Video"},
            "value_type": "integer",
            "_provenance": {"declared_in": "OptionsClass", "member": "ScreenWidth"},
        }
        with self.assertRaisesRegex(ValueError, "share the public route id"):
            extract_engine._order_shared_route_scopes(
                "ScreenWidth", [dict(scope), dict(scope)])


class TrackedCatalogRouteTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.keys = validate_manual.read_yaml(
            TOOLS.parent / "data" / "ini-keys.yaml")

    def shared_route_keys(self):
        return [
            name for name, entry in self.keys.items()
            if len(validate_manual.scope_route_ids(entry))
            != len({
                validate_manual.scope_route_base(scope)
                for scope in entry["scopes"]
            })
        ]

    def test_every_published_scope_is_in_its_recorded_order(self):
        for name, entry in self.keys.items():
            with self.subTest(key=name):
                self.assertEqual(
                    validate_manual.scope_route_order_errors(
                        name, entry["scopes"]),
                    [])

    def test_a_swapped_pair_is_reported_rather_than_silently_republished(self):
        shared = self.shared_route_keys()
        self.assertTrue(shared, "no key exercises a suffixed scope route")
        indistinguishable = set()
        for name in shared:
            scopes = list(reversed(self.keys[name]["scopes"]))
            errors = validate_manual.scope_route_order_errors(name, scopes)
            if errors:
                self.assertIn("route id", errors[0])
            else:
                indistinguishable.add(name)
        self.assertEqual(
            indistinguishable, {"Official"},
            "only Official's two [Basic] reads agree on every published field")


if __name__ == "__main__":
    unittest.main()

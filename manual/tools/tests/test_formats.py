from pathlib import Path
import sys
import tempfile
import unittest

import yaml


TOOLS = Path(__file__).resolve().parents[1]
MANUAL = TOOLS.parent
sys.path.insert(0, str(TOOLS))

import formats
import schema_validation


class CurrentFormatCatalogTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.keys = yaml.safe_load(
            (MANUAL / "data" / "ini-keys.yaml").read_text(encoding="utf-8"))
        cls.catalog = formats.load_formats()

    def test_catalog_covers_every_variant_and_preserves_mapping_routes(self):
        # A page whose frontmatter omits format_id is skipped rather than rejected,
        # so every authored file is required to arrive rather than counted.
        authored = sorted((MANUAL / "content" / "formats").glob("*.md"))
        self.assertTrue(authored)
        self.assertEqual(
            {record["_slug"] for record in self.catalog.values()},
            {path.stem for path in authored},
        )
        self.assertEqual(
            {record["kind"] for record in self.catalog.values()},
            formats.FORMAT_KINDS,
        )
        self.assertEqual(self.catalog["teamtypes"]["route"], "/mapping/team-types/")
        self.assertEqual(self.catalog["taskforces"]["route"], "/mapping/task-forces/")
        self.assertEqual(self.catalog["scripts"]["route"], "/mapping/scripts/")
        self.assertEqual(self.catalog["ai_triggers"]["route"], "/mapping/ai-triggers/")

    def test_current_catalog_contracts_sources_and_queries_validate(self):
        errors = []
        records = formats.validate_formats(errors, self.keys)
        self.assertEqual(errors, [])
        self.assertEqual(records.keys(), self.catalog.keys())

    def test_generated_scope_queries_derive_expected_reference_counts(self):
        def matches(format_id):
            queries = self.catalog[format_id]["key_scopes"]
            return [
                (key, scope)
                for key, record in self.keys.items()
                for scope in record["scopes"]
                if any(formats._query_matches(scope, query) for query in queries)
            ]

        map_seed = matches("map-seed")
        theater = matches("theater-control")
        self.assertTrue(map_seed)
        self.assertTrue(theater)
        self.assertEqual(
            {scope["section"]["name"] for _, scope in map_seed}, {"RandomMap"})
        # Every [RandomMap] scope in the tree has to be selected, not merely every
        # selected scope be a [RandomMap] one, so the query cannot quietly narrow.
        self.assertEqual(
            len(map_seed),
            sum(
                scope["section"].get("name") == "RandomMap"
                for record in self.keys.values()
                for scope in record["scopes"]
            ),
        )
        self.assertEqual(
            {scope["section"]["kind"] for _, scope in theater},
            {"literal", "identifier"},
        )

    def test_binary_roles_use_the_closed_public_vocabulary(self):
        binary = [record for record in self.catalog.values() if record["kind"] == "binary"]
        self.assertEqual({record["role"] for record in binary}, formats.BINARY_ROLES)


class FormatContractTests(unittest.TestCase):
    def failures(self, document):
        return schema_validation.errors_for(
            document, "authored-format.schema.json", "format")

    def test_variant_fields_are_closed_and_binary_role_is_an_enum(self):
        valid = {
            "format_id": "example",
            "title": "Example",
            "summary": "Defines an example binary file.",
            "kind": "binary",
            "extensions": [".BIN"],
            "role": "archive",
            "source_files": ["code/example.cpp"],
        }
        self.assertEqual(self.failures(valid), [])
        invalid_role = {**valid, "role": "container"}
        self.assertTrue(self.failures(invalid_role))
        invalid_variant = {**valid, "files": ["example.ini"]}
        self.assertTrue(self.failures(invalid_variant))

    def test_registration_definition_is_exactly_one_section_or_value(self):
        base = {
            "format_id": "example",
            "title": "Example",
            "summary": "Defines an example registry.",
            "kind": "registry",
            "files": ["rules.ini"],
            "source_files": ["code/example.cpp"],
        }
        section = {
            "section": "BuildingTypes",
            "id_from": "value",
            "entry_section": "<BuildingType ID>",
        }
        value = {
            "section": "Sides",
            "id_from": "key",
            "value": "HouseType ID list",
        }
        self.assertEqual(self.failures({**base, "registrations": [section]}), [])
        self.assertEqual(self.failures({**base, "registrations": [value]}), [])
        self.assertTrue(self.failures({**base, "registrations": [{**section, **value}]}))
        missing = {"section": "Sides", "id_from": "key"}
        self.assertTrue(self.failures({**base, "registrations": [missing]}))

    def test_catalog_parser_rejects_duplicate_ids_and_routes(self):
        first = "---\nformat_id: one\ntitle: One\n---\n"
        duplicate_id = "---\nformat_id: one\ntitle: Two\n---\n"
        duplicate_route = "---\nformat_id: two\ntitle: Two\n---\n"
        with self.assertRaisesRegex(ValueError, "duplicate format ID"):
            formats.parse_catalog([("one.md", first), ("two.md", duplicate_id)])
        with self.assertRaisesRegex(ValueError, "already owned"):
            formats.parse_catalog([("one.md", first), ("one.md", duplicate_route)])

    def test_route_overrides_are_reserved_for_migrated_mapping_formats(self):
        valid = {
            "format_id": "scripts",
            "title": "Scripts",
            "summary": "Defines ScriptType records.",
            "kind": "file",
            "filenames": ["rules.ini"],
            "route": "/mapping/scripts/",
            "source_files": ["code/script.cpp"],
        }
        self.assertEqual(self.failures(valid), [])
        self.assertTrue(self.failures({**valid, "format_id": "example"}))

    def test_scaffold_frontmatter_is_kind_specific_and_stays_action_required(self):
        for kind in sorted(formats.FORMAT_KINDS):
            with self.subTest(kind=kind):
                frontmatter = formats.scaffold_frontmatter("new-format", kind)
                self.assertEqual(frontmatter["format_id"], "new-format")
                self.assertEqual(frontmatter["kind"], kind)
                self.assertTrue(formats._contains_todo(frontmatter))
        with self.assertRaisesRegex(ValueError, "unknown format kind"):
            formats.scaffold_frontmatter("new-format", "container")

    def test_structural_validator_rejects_sources_and_companions(self):
        with tempfile.TemporaryDirectory() as folder:
            manual = Path(folder) / "manual"
            content = manual / "content" / "formats"
            content.mkdir(parents=True)
            (content / "example.md").write_text(
                "---\n"
                "format_id: example\n"
                "title: Example\n"
                "summary: Defines an example binary.\n"
                "kind: binary\n"
                "extensions: [.BIN]\n"
                "role: archive\n"
                "companion_formats: [example, missing]\n"
                "source_files: [code/missing.cpp]\n"
                "---\n",
                encoding="utf-8",
            )
            errors = []
            formats.validate_formats(errors, {}, manual)

        self.assertTrue(any("source path does not exist" in error for error in errors))
        self.assertTrue(any("cannot be its own companion" in error for error in errors))
        self.assertTrue(any("unknown companion format 'missing'" in error for error in errors))

    def test_structural_validator_reports_stale_queries_and_field_gaps(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            manual = root / "manual"
            content = manual / "content" / "formats"
            source = root / "code" / "example.cpp"
            content.mkdir(parents=True)
            source.parent.mkdir(parents=True)
            source.write_text("// source\n", encoding="utf-8")
            (content / "example.md").write_text(
                "---\n"
                "format_id: example\n"
                "title: Example\n"
                "summary: Defines an example record.\n"
                "kind: record\n"
                "files: [example.ini]\n"
                "section: Examples\n"
                "syntax: '<ID>=<first>,<second>'\n"
                "fields:\n"
                "  - { position: 1, label: First, value: integer, required: true }\n"
                "  - { position: 3, label: Second, value: integer, required: false }\n"
                "key_scopes:\n"
                "  - { file: missing.ini }\n"
                "source_files: [code/example.cpp]\n"
                "---\n",
                encoding="utf-8",
            )
            errors = []
            formats.validate_formats(errors, {"Known": {"scopes": []}}, manual)
            self.assertTrue(any("consecutive positions" in error for error in errors))
            self.assertTrue(any("matches no generated scope" in error for error in errors))


if __name__ == "__main__":
    unittest.main()

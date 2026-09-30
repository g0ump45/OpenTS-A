from pathlib import Path
import sys
import tempfile
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import extract
import ini_inventory
import schema_validation
import section_selectors
import validate_manual


def generated_scope(section, read_from=None):
    scope = {
        "applies_to": ["UnitType"],
        "file": "rules.ini",
        "section": section,
        "value_type": "integer",
        "level": "UnitTypeClass",
        "status": "generated",
        "_provenance": {
            "default_candidate": None,
            "declared_in": "UnitTypeClass",
            "member": "Value",
            "source": "code/unittype.cpp",
            "guard": None,
        },
    }
    if read_from is not None:
        scope["read_from"] = read_from
    return {"Visible": {"key": "Visible", "scopes": [scope]}}


class SectionSelectorUnitTests(unittest.TestCase):
    def test_closed_selector_shapes(self):
        self.assertEqual(
            section_selectors.literal("General"),
            {"kind": "literal", "name": "General"},
        )
        self.assertEqual(
            section_selectors.identifier("tile-set"),
            {"kind": "identifier", "source": "tile-set"},
        )
        self.assertEqual(
            section_selectors.image(),
            {"kind": "image", "fallback": "object-type"},
        )
        self.assertEqual(section_selectors.image(None), {"kind": "image"})
        with self.assertRaises(section_selectors.SectionSelectorError):
            section_selectors.literal("[General]")
        with self.assertRaises(section_selectors.SectionSelectorError):
            section_selectors.identifier("weather")
        with self.assertRaises(section_selectors.SectionSelectorError):
            section_selectors.image("house")
        with self.assertRaises(section_selectors.SectionSelectorError):
            section_selectors.require({"kind": "literal", "name": "General", "extra": True})

    def test_legacy_main_and_read_source_values_normalize_for_comparison(self):
        legacy = {
            "section": "[General]",
            "read_from": [{
                "section": "the entry named by this object's Image=",
            }],
        }
        current = {
            "section": section_selectors.literal("General"),
            "read_from": [{"section": section_selectors.image()}],
        }
        self.assertEqual(
            section_selectors.normalize_scope(legacy),
            section_selectors.normalize_scope(current),
        )

    def test_unclassified_cpp_expression_fails_with_context(self):
        with self.assertRaisesRegex(
                section_selectors.SectionSelectorError,
                "code/reader.cpp:7.*unclassified.*mystery"):
            section_selectors.classify(
                "mystery", context="code/reader.cpp:7 key 'Visible'")

    def test_global_extraction_fails_closed(self):
        with tempfile.TemporaryDirectory() as folder:
            source = Path(folder) / "reader.cpp"
            source.write_text(
                "bool Reader::Load(CCINIClass const & ini)\n"
                "{\n"
                "    Value = ini.Get_Int(mystery, \"Visible\", Value);\n"
                "    return true;\n"
                "}\n",
                encoding="latin-1",
            )
            with self.assertRaisesRegex(ValueError, "unclassified.*mystery"):
                extract.extract_globals(
                    source,
                    "Reader",
                    ["Load"],
                    {"file": "rules.ini", "group": "synthetic"},
                )


class SectionSelectorSchemaTests(unittest.TestCase):
    def failures(self, document):
        return schema_validation.errors_for(
            document, "generated-ini-keys.schema.json", "generated")

    def test_scope_and_read_sources_share_the_exact_contract(self):
        read_from = [
            {
                "file": "rules.ini",
                "section": section_selectors.literal("General"),
                "value_type": "integer",
                "applies_to": ["UnitType"],
            },
            {
                "file": "art.ini",
                "section": section_selectors.image(),
                "value_type": "integer",
                "applies_to": ["UnitType"],
            },
        ]
        document = generated_scope(
            section_selectors.identifier("object-type"), read_from)
        self.assertEqual(self.failures(document), [])

        document["Visible"]["scopes"][0]["read_from"][1]["section"] = "[Unit]"
        self.assertTrue(self.failures(document))

    def test_strings_bracketed_names_and_unknown_sources_are_rejected(self):
        invalid = (
            "[General]",
            {"kind": "literal", "name": "[General]"},
            {"kind": "identifier", "source": "weather"},
            {"kind": "image", "fallback": "house"},
            {"kind": "image", "fallback": None},
        )
        for section in invalid:
            with self.subTest(section=section):
                self.assertTrue(self.failures(generated_scope(section)))

    def test_python_validator_reports_scope_and_read_source_context(self):
        document = generated_scope("unclassified", [
            {
                "file": "rules.ini",
                "section": section_selectors.literal("General"),
                "value_type": "integer",
                "applies_to": ["UnitType"],
            },
            {
                "file": "art.ini",
                "section": "also unclassified",
                "value_type": "integer",
                "applies_to": ["UnitType"],
            },
        ])
        errors = []
        validate_manual.validate_section_selectors(errors, document)
        self.assertTrue(any("Visible scope 1 section" in error for error in errors))
        self.assertTrue(any("read_from 2 section" in error for error in errors))


class CurrentExtractionSelectorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.keys, _, _, _ = extract._extract_all(ini_inventory.load_manifest())

    def selector_from(self, key, source_file):
        for scope in self.keys[key]["scopes"]:
            source = (scope.get("_provenance") or {}).get("source", "")
            if source == f"code/{source_file}":
                return scope["section"]
        self.fail(f"{key}: no scope extracted from code/{source_file}")

    def test_every_scope_and_read_source_is_classified(self):
        for key, entry in self.keys.items():
            for scope in entry["scopes"]:
                with self.subTest(key=key, source=scope["_provenance"]["source"]):
                    section_selectors.require(scope["section"])
                for source in scope.get("read_from", []):
                    section_selectors.require(source["section"])

    def test_source_backed_adapters_cover_every_identifier_kind(self):
        # Coverage is the claim, so it is read off the extraction rather than from a
        # roster of representative keys that rots whenever a read moves file.
        exercised = {
            scope["section"]["source"]
            for entry in self.keys.values()
            for scope in entry["scopes"]
            if scope["section"]["kind"] == "identifier"
        }
        self.assertEqual(
            exercised,
            set(section_selectors.IDENTIFIER_SOURCES) - {"base-owner-house"},
        )

    def test_image_sections_record_whether_an_object_entry_backs_them(self):
        self.assertEqual(
            self.selector_from("Voxel", "objtype.cpp"), section_selectors.image())
        # BulletTypeClass::Read_INI re-reads Image= with an empty default,
        # so its own art reads have no object entry to fall back to.
        self.assertEqual(
            self.selector_from("AnimLow", "bullettype.cpp"),
            section_selectors.image(None))


if __name__ == "__main__":
    unittest.main()

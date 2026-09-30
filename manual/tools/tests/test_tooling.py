import argparse
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

import yaml


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import contributor
import extract
import ini_inventory
from io_utils import atomic_write_text
import schema_validation
import scripting


class AtomicOutputTests(unittest.TestCase):
    def test_atomic_write_replaces_complete_contents_without_temp_files(self):
        with tempfile.TemporaryDirectory() as folder:
            target = Path(folder) / "generated.yaml"
            target.write_text("old\n", encoding="utf-8")
            atomic_write_text(target, "new\n")
            self.assertEqual(target.read_text(encoding="utf-8"), "new\n")
            self.assertEqual(list(Path(folder).glob(".*.tmp")), [])

    def test_generators_serialize_before_atomic_destination_replace(self):
        for module in (extract, scripting):
            with self.subTest(generator=module.__name__):
                source = Path(module.__file__).read_text(encoding="utf-8")
                serialization = source.index("safe_dump")
                replacement = source.index("atomic_write_text", serialization)
                self.assertLess(serialization, replacement)
                self.assertNotRegex(
                    source,
                    r'open\((?:arguments\.(?:consolidated|out)|args\.(?:consolidated|out)),\s*["\']w["\']')


class SchemaContractTests(unittest.TestCase):
    def test_authored_status_is_rejected_and_generated_level_is_required(self):
        authored = schema_validation.errors_for(
            {"key": "Speed", "status": "draft"},
            "authored-key.schema.json", "key page")
        self.assertTrue(any("status" in error for error in authored))

        generated = {
            "Speed": {
                "key": "Speed",
                "scopes": [{
                    "applies_to": ["UnitType"],
                    "file": "rules.ini",
                    "section": {
                        "kind": "identifier",
                        "source": "object-type",
                    },
                    "value_type": "speed",
                    "status": "generated",
                    "_provenance": {
                        "default_candidate": None,
                        "declared_in": "TechnoTypeClass",
                        "member": "Speed",
                        "source": "code/techtype.cpp",
                        "guard": None,
                    },
                }],
            },
        }
        failures = schema_validation.errors_for(
            generated, "generated-ini-keys.schema.json", "generated")
        self.assertTrue(any("level" in error for error in failures))

    def test_provenance_cites_a_file_rather_than_a_position(self):
        """A position rots when unrelated code above it moves."""

        scope = {
            "applies_to": ["UnitType"],
            "file": "rules.ini",
            "section": {"kind": "identifier", "source": "object-type"},
            "value_type": "speed",
            "level": "TechnoTypeClass",
            "status": "generated",
            "_provenance": {
                "default_candidate": None,
                "declared_in": "TechnoTypeClass",
                "member": "Speed",
                "source": "code/techtype.cpp:1",
                "guard": None,
            },
        }
        failures = schema_validation.errors_for(
            {"Speed": {"key": "Speed", "scopes": [scope]}},
            "generated-ini-keys.schema.json", "generated")
        self.assertTrue(any("source" in error for error in failures))

        data = Path(TOOLS).parent / "data"
        keys = yaml.safe_load((data / "ini-keys.yaml").read_text(encoding="utf-8"))
        for name, entry in keys.items():
            for index, tracked in enumerate(entry["scopes"]):
                with self.subTest(key=name, scope=index):
                    self.assertNotIn(":", tracked["_provenance"]["source"])
        commands = yaml.safe_load(
            (data / "commands.yaml").read_text(encoding="utf-8"))
        for group in commands.values():
            for record in group:
                with self.subTest(command=record["id"]):
                    self.assertNotIn("line", record["_provenance"])

    def test_every_schema_is_valid_draft_2020_12(self):
        names = {path.name for path in schema_validation.SCHEMA_DIRECTORY.glob("*.json")}
        self.assertTrue(names)
        for name in names:
            with self.subTest(name=name):
                schema_validation.load_schema(name)


class InventoryTests(unittest.TestCase):
    def test_scanner_ignores_comments_and_section_only_calls(self):
        with tempfile.TemporaryDirectory() as folder:
            code = Path(folder)
            source = code / "reader.cpp"
            source.write_text(
                """
                bool UnitTypeClass::Read_INI(CCINIClass const & ini)
                {
                    // ini.Get_Int(Name(), "Commented", 0);
                    Value = ini.Get_Int(
                        Name(),
                        "VisibleKey",
                        Value);
                    ini.Get_TextBlock("Briefing", Buffer, sizeof(Buffer));
                    return true;
                }
                """,
                encoding="latin-1",
            )
            sites = ini_inventory.discover_literal_reads(code)
        self.assertEqual([(site.key, site.function) for site in sites], [
            ("VisibleKey", "UnitTypeClass::Read_INI"),
        ])

    def test_a_numeric_entry_name_is_a_discovered_site(self):
        with tempfile.TemporaryDirectory() as folder:
            code = Path(folder)
            source = code / "reader.cpp"
            source.write_text(
                'void Read_Digest(void) { ini.Get_String("Digest", "1", '
                '"none", buffer, sizeof(buffer)); }',
                encoding="latin-1",
            )
            sites = ini_inventory.discover_literal_reads(code)
        self.assertEqual(
            [(site.key, site.function) for site in sites],
            [("1", "Read_Digest")])

    def test_a_trailing_default_is_not_read_as_an_entry_name(self):
        self.assertIsNone(
            ini_inventory.literal_key(["section", "entry", '""', "buffer"]))
        self.assertEqual(
            ini_inventory.literal_key(["section", '"Image"', '""']), "Image")
        self.assertIsNone(
            ini_inventory.literal_key(['"Digest"', "buffer", "size"]))

    def test_an_excluded_rule_removes_a_read_an_enrolled_unit_owns(self):
        manifest = {
            "version": 1,
            "reader_exclusions": [],
            "site_exclusions": [{
                "path": "code/reader.cpp",
                "function": "OwnedClass::Read_INI",
                "keys": ["1"],
                "classification": "excluded",
                "reason": "A generated checksum rather than an authored setting.",
            }],
        }
        with tempfile.TemporaryDirectory() as folder:
            code = Path(folder)
            source = code / "reader.cpp"
            source.write_text(
                'bool OwnedClass::Read_INI(CCINIClass const & ini) '
                '{ ini.Get_String("Digest", "1", "none", buf, sizeof(buf)); '
                'return true; }',
                encoding="latin-1",
            )
            sites = ini_inventory.discover_literal_reads(code)
            records = {"OwnedClass": [
                {"key": "1", "src": "reader.cpp", "line": sites[0].line}]}
            kept = ini_inventory.drop_suppressed(records, manifest, sites)
            errors, summary = ini_inventory.validate_inventory(
                kept, manifest, code, sites=sites)
        self.assertEqual(kept, {"OwnedClass": []})
        self.assertEqual(errors, [])
        self.assertEqual(summary["excluded"], 1)

    def test_manifest_rules_are_function_and_key_based_not_line_fingerprints(self):
        manifest = ini_inventory.load_manifest()
        for row in manifest["site_exclusions"]:
            self.assertNotIn("line", row)
            self.assertIn("keys", row)
            self.assertTrue(row["reason"].strip())

    def test_current_literal_read_inventory_is_fully_classified(self):
        manifest = ini_inventory.load_manifest()
        tree = extract.load_hierarchy()
        records = {}
        configured = set(extract.UNITS)
        configured.update(
            (filename, cls)
            for filename, cls, methods, _ in extract.GLOBAL_UNITS
            if "Read_INI" in methods)
        units = list(extract.UNITS) + ini_inventory.discover_read_ini_units(
            extract.CODE_DIR, manifest, configured)
        for filename, cls in units:
            rows, _ = extract.extract_file(
                os.path.join(extract.CODE_DIR, filename), cls, tree)
            records[f"{cls}/{filename}"] = rows
        for filename, cls, methods, options in extract.GLOBAL_UNITS:
            rows, _ = extract.extract_globals(
                os.path.join(extract.CODE_DIR, filename), cls, methods, options)
            records[f"{cls}/{filename}/{methods[0]}"] = rows
        sites = ini_inventory.discover_literal_reads(extract.CODE_DIR)
        records = ini_inventory.drop_suppressed(records, manifest, sites)
        failures, summary = ini_inventory.validate_inventory(
            records, manifest, extract.CODE_DIR, sites=sites)
        self.assertEqual(failures, [])
        self.assertEqual(summary["unclassified"], 0)
        self.assertGreater(summary["extracted"], 1000)


class DoctorTests(unittest.TestCase):
    def test_doctor_reports_verified_toolchain_from_authority_files(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            tools = root / "manual" / "tools"
            site = root / "manual" / "site"
            tools.mkdir(parents=True)
            (site / "node_modules").mkdir(parents=True)
            (tools / ".python-version").write_text(
                platform_version := __import__("platform").python_version(), encoding="utf-8")
            (tools / "requirements.txt").write_text("PyYAML==6.0.2\n", encoding="utf-8")
            (site / ".nvmrc").write_text("22.20.0\n", encoding="utf-8")
            (site / "package.json").write_text(json.dumps({
                "engines": {"node": "22.20.0"},
                "packageManager": "npm@11.18.0",
            }), encoding="utf-8")
            with (
                mock.patch.object(contributor, "ROOT", root),
                mock.patch.object(contributor, "TOOLS", tools),
                mock.patch.object(contributor, "SITE", site),
                mock.patch.object(contributor.shutil, "which", side_effect=lambda name: name),
                mock.patch.object(
                    contributor, "_version_output",
                    side_effect=lambda executable, argument="--version": {
                        "node": "22.20.0", "npm": "11.18.0"}[executable]),
                mock.patch.object(contributor.importlib.metadata, "version", return_value="6.0.2"),
            ):
                verified, actions = contributor.doctor(verbose=True)
        self.assertEqual(actions, [])
        self.assertTrue(any(platform_version in row for row in verified))
        self.assertTrue(any("Node 22.20.0" in row for row in verified))


class ScaffoldTests(unittest.TestCase):
    def _paths(self, root):
        manual = root / "manual"
        data = manual / "data"
        data.mkdir(parents=True)
        return manual, data

    def test_key_scaffold_uses_canonical_route_scope_and_refuses_overwrite(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            manual, data = self._paths(root)
            record = {
                "Armor": {
                    "key": "Armor",
                    "scopes": [
                        {"applies_to": ["AircraftType"]},
                        {"applies_to": ["HouseType"]},
                    ],
                },
            }
            (data / "ini-keys.yaml").write_text(
                yaml.safe_dump(record), encoding="utf-8")
            with (
                mock.patch.object(contributor, "ROOT", root),
                mock.patch.object(contributor, "MANUAL", manual),
                mock.patch.object(contributor, "DATA", data),
            ):
                with self.assertRaisesRegex(ValueError, "multiple meanings"):
                    contributor.scaffold_key("Armor")
                contributor.scaffold_key("Armor", "aircrafttype")
                target = manual / "content" / "keys" / "armor--aircrafttype.md"
                self.assertTrue(target.is_file())
                with self.assertRaisesRegex(ValueError, "refusing to overwrite"):
                    contributor.scaffold_key("Armor", "aircrafttype")

    def test_change_scaffold_derives_development_release(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            manual, data = self._paths(root)
            (data / "releases.yaml").write_text(
                "releases:\n  - version: 0.2.0\n    status: development\n",
                encoding="utf-8")
            arguments = argparse.Namespace(
                identifier="add-fast-mode", title=None, category="feature",
                target_type="key", target_id="FastMode", scope="global-rules",
                effect="added", credit=["Programmer"])
            with (
                mock.patch.object(contributor, "ROOT", root),
                mock.patch.object(contributor, "MANUAL", manual),
                mock.patch.object(contributor, "DATA", data),
            ):
                contributor.scaffold_change(arguments)
            result = (manual / "changes" / "add-fast-mode.md").read_text(encoding="utf-8")
        self.assertIn("release: 0.2.0", result)
        self.assertIn("scope: global-rules", result)
        self.assertIn("credit:", result)

    def test_change_scaffold_marks_missing_credit(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            manual, data = self._paths(root)
            (data / "releases.yaml").write_text(
                "releases:\n  - version: 0.2.0\n    status: development\n",
                encoding="utf-8")
            arguments = argparse.Namespace(
                identifier="fix-unattributed", title=None, category="fix",
                target_type="key", target_id="FastMode", scope=None,
                effect="changed", credit=[])
            with (
                mock.patch.object(contributor, "ROOT", root),
                mock.patch.object(contributor, "MANUAL", manual),
                mock.patch.object(contributor, "DATA", data),
            ):
                contributor.scaffold_change(arguments)
            result = (manual / "changes" / "fix-unattributed.md").read_text(
                encoding="utf-8")
        self.assertIn("TODO: name the author", result)


if __name__ == "__main__":
    unittest.main()

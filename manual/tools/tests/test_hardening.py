from contextlib import redirect_stderr, redirect_stdout
import argparse
import io
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import contributor
import extract
import ini_inventory
import scripting
import validate_manual


class DependencyLightCommandTests(unittest.TestCase):
    def test_doctor_starts_without_site_packages(self):
        result = subprocess.run(
            [sys.executable, "-S", str(TOOLS / "manage.py"), "doctor"],
            cwd=TOOLS.parents[1],
            text=True,
            encoding="utf-8",
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        self.assertIn("VERIFIED", result.stdout)
        self.assertIn("ACTION REQUIRED", result.stdout)
        self.assertNotIn("Traceback", result.stdout)
        self.assertNotIn("ModuleNotFoundError", result.stdout)

    def test_scope_is_rejected_for_non_key_non_change_scaffolds(self):
        parser = argparse.ArgumentParser()
        commands = parser.add_subparsers(dest="command", required=True)
        contributor.add_parsers(commands)
        arguments = parser.parse_args([
            "scaffold", "scripting", "TACTION_WIN", "--scope", "global",
        ])
        with redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
            contributor.validate_scaffold_arguments(parser, arguments)


class DirectGeneratorTests(unittest.TestCase):
    def test_both_generators_serialize_before_atomic_publish(self):
        extract_source = Path(extract.__file__).read_text(encoding="utf-8")
        scripting_source = Path(scripting.__file__).read_text(encoding="utf-8")
        for source in (extract_source, scripting_source):
            serialization = source.index("safe_dump")
            replacement = source.index("atomic_write_text", serialization)
            self.assertLess(serialization, replacement)
        self.assertNotIn('open(arguments.consolidated, "w"', extract_source)
        self.assertNotIn('open(arguments.out, "w"', scripting_source)


class InventoryClassificationTests(unittest.TestCase):
    def _source_tree(self, text):
        temporary = tempfile.TemporaryDirectory()
        root = Path(temporary.name)
        (root / "reader.cpp").write_text(text, encoding="latin-1")
        self.addCleanup(temporary.cleanup)
        return root

    @staticmethod
    def _manifest(rules=(), readers=()):
        return {
            "version": 1,
            "reader_exclusions": list(readers),
            "site_exclusions": list(rules),
        }

    def test_new_literal_in_exact_rule_is_unclassified(self):
        root = self._source_tree(
            'void Legacy() { ini.Get_Int("Section", "Known", 0); '
            'ini.Get_Int("Section", "NewKey", 0); }')
        manifest = self._manifest([{
            "path": "code/reader.cpp",
            "function": "Legacy",
            "keys": ["Known"],
            "classification": "excluded",
            "reason": "Synthetic non-public legacy resource field.",
        }])
        errors, summary = ini_inventory.validate_inventory({}, manifest, root)
        self.assertEqual(summary["unclassified"], 1)
        self.assertTrue(any("NewKey" in error for error in errors))
        self.assertFalse(any("Known" in error and "unclassified" in error for error in errors))

    def test_stale_site_and_reader_rules_fail(self):
        root = self._source_tree(
            'bool Present::Read_INI(CCINIClass const & ini) { return true; }')
        manifest = self._manifest(
            rules=[{
                "path": "code/reader.cpp",
                "function": "Legacy",
                "keys": ["Gone"],
                "classification": "excluded",
                "reason": "Synthetic field that no longer exists anywhere.",
            }],
            readers=[{
                "path": "code/reader.cpp",
                "function": "Gone::Read_INI",
                "reason": "Synthetic reader that no longer exists anywhere.",
            }],
        )
        errors, _ = ini_inventory.validate_inventory({}, manifest, root)
        self.assertTrue(any("stale site classification" in error for error in errors))
        self.assertTrue(any("stale reader exclusion" in error for error in errors))

    def test_new_read_ini_class_is_discovered_without_manifest_edit(self):
        root = self._source_tree(
            'bool NewReader::Read_INI(CCINIClass const & ini) '
            '{ Value = ini.Get_Int(Name(), "NewSetting", Value); return true; }')
        units = ini_inventory.discover_read_ini_units(
            root, self._manifest(), configured=())
        self.assertEqual(units, [("reader.cpp", "NewReader")])


class ValidationHardeningTests(unittest.TestCase):
    def test_level_and_section_selector_migrations_are_not_semantic_changes(self):
        old = {
            "scopes": [{
                "applies_to": ["UnitType"],
                "file": "rules.ini",
                "section": "the object's own entry",
                "value_type": "integer",
                "_provenance": {"declared_in": "TechnoTypeClass"},
            }],
        }
        current = {
            "scopes": [{
                **old["scopes"][0],
                "section": {"kind": "identifier", "source": "object-type"},
                "level": "TechnoTypeClass",
            }],
        }
        self.assertEqual(
            validate_manual.semantic_key(old),
            validate_manual.semantic_key(current))

    def test_case_collision_requires_existing_symmetric_peer(self):
        errors = []
        validate_manual.validate_case_collisions(errors, {
            "DropPod": {
                "case_collides_with": ["Droppod"],
                "scopes": [],
            },
            "Droppod": {"scopes": []},
        })
        self.assertTrue(any("reciprocal" in error for error in errors))

    def test_todo_marker_is_rejected(self):
        with tempfile.TemporaryDirectory() as folder:
            manual = Path(folder)
            page = manual / "content" / "keys" / "test.md"
            page.parent.mkdir(parents=True)
            (manual / "changes").mkdir()
            page.write_text("---\nkey: Test\n---\n\nTODO: explain this\n", encoding="utf-8")
            with mock.patch.object(validate_manual, "MANUAL", manual):
                errors = []
                validate_manual.validate_placeholders(errors)
        self.assertTrue(any("unfinished scaffold marker" in error for error in errors))

    def test_actionable_followups_include_ready_commands(self):
        omission = validate_manual._actionable(
            "Armor[aircrafttype]: authored when_omitted metadata is required")
        lifecycle = validate_manual._actionable(
            "action:TACTION_NEW: add a change target with effect: added")
        self.assertIn(
            "scaffold key Armor --scope aircrafttype", omission)
        self.assertIn(
            "scaffold change added-taction-new --target-type action "
            "--target-id TACTION_NEW --effect added",
            lifecycle,
        )


if __name__ == "__main__":
    unittest.main()

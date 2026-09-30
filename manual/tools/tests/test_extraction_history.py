from pathlib import Path
import sys
import tempfile
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

from extraction_history import historical_corrections


def scope(source="code/reader.cpp", applies_to="UnitType", value_type="integer",
          member=None):
    return {
        "applies_to": [applies_to],
        "file": "rules.ini",
        "section": {"kind": "identifier", "source": "object-type"},
        "value_type": value_type,
        "level": "UnitTypeClass",
        "_provenance": {
            "source": source,
            "declared_in": "UnitTypeClass",
            "member": member,
        },
    }


class ExtractionHistoryTests(unittest.TestCase):
    def _tree(self, text):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        root = Path(temporary.name)
        source = root / "code" / "reader.cpp"
        source.parent.mkdir()
        source.write_text(text, encoding="latin-1")
        return root

    def test_preexisting_typed_literal_read_is_a_metadata_correction(self):
        text = 'Value = ini.Get_Int(Name(), "Visible", Value);\n'
        root = self._tree(text)
        current = {"Visible": {"scopes": [scope()]}}

        result = historical_corrections(
            current, {}, root, lambda path: text)

        self.assertEqual(result, {"Visible"})

    def test_branch_added_typed_read_still_requires_lifecycle_metadata(self):
        current_text = (
            'Old = ini.Get_Int(Name(), "Old", Old);\n'
            'New = ini.Get_Int(Name(), "New", New);\n')
        base_text = 'Old = ini.Get_Int(Name(), "Old", Old);\n'
        root = self._tree(current_text)
        current = {"New": {"scopes": [scope()]}}

        result = historical_corrections(
            current, {}, root, lambda path: base_text)

        self.assertEqual(result, set())

    def test_preexisting_scope_reclassification_is_symmetric_correction(self):
        text = 'Value = ini.Get_Int(Name(), "Shared", Value);\n'
        root = self._tree(text)
        base = {
            "Shared": {"scopes": [
                scope(applies_to="UnitType"),
            ]},
        }
        current = {
            "Shared": {"scopes": [
                scope(applies_to="global rules"),
            ]},
        }

        result = historical_corrections(
            current, base, root, lambda path: text)

        self.assertEqual(result, {"Shared"})

    def test_base_only_scope_must_still_have_a_typed_read_in_current_source(self):
        base_text = (
            'First = ini.Get_Int(Name(), "Shared", First);\n'
            'Second = ini.Get_Int(Name(), "Shared", Second);\n')
        current_text = 'First = ini.Get_Int(Name(), "Shared", First);\n'
        root = self._tree(current_text)
        base = {
            "Shared": {"scopes": [
                scope(applies_to="UnitType"),
                scope(applies_to="AircraftType"),
            ]},
        }
        current = {
            "Shared": {"scopes": [
                scope(applies_to="UnitType"),
            ]},
        }

        result = historical_corrections(
            current, base, root, lambda path: base_text)

        self.assertEqual(result, set())

    def test_base_only_scope_that_still_exists_can_be_extractor_correction(self):
        text = (
            'First = ini.Get_Int(Name(), "Shared", First);\n'
            'Second = ini.Get_Int(Name(), "Shared", Second);\n')
        root = self._tree(text)
        base = {
            "Shared": {"scopes": [
                scope(applies_to="UnitType"),
                scope(applies_to="AircraftType"),
            ]},
        }
        current = {
            "Shared": {"scopes": [
                scope(applies_to="UnitType"),
            ]},
        }

        result = historical_corrections(
            current, base, root, lambda path: text)

        self.assertEqual(result, {"Shared"})

    def test_provenance_recorded_with_a_line_still_resolves(self):
        text = 'Value = ini.Get_Int(Name(), "Visible", Value);\n'
        root = self._tree(text)
        base = {"Visible": {"scopes": [
            scope("code/reader.cpp:1", applies_to="UnitType")]}}
        current = {"Visible": {"scopes": [
            scope(applies_to="global rules")]}}

        result = historical_corrections(
            current, base, root, lambda path: text)

        self.assertEqual(result, {"Visible"})

    def test_moved_read_is_a_correction_rather_than_an_engine_change(self):
        base_text = 'Value = ini.Get_Int(Name(), "Visible", Value);\n'
        current_text = "\n\n\n" + base_text
        root = self._tree(current_text)
        base = {"Visible": {"scopes": [scope(applies_to="UnitType")]}}
        current = {"Visible": {"scopes": [scope(applies_to="global rules")]}}

        result = historical_corrections(
            current, base, root, lambda path: base_text)

        self.assertEqual(result, {"Visible"})

    def test_computed_entry_name_resolves_through_the_recorded_member(self):
        text = (
            'char buffer[32];\n'
            'sprintf(buffer, "BurstDelay%d", index);\n'
            'BurstDelay[index] = ini.Get_Int(Name(), buffer, BurstDelay[index]);\n')
        root = self._tree(text)
        current = {"BurstDelay0": {"scopes": [scope(member="BurstDelay")]}}

        result = historical_corrections(
            current, {}, root, lambda path: text)

        self.assertEqual(result, {"BurstDelay0"})

    def test_one_of_two_reads_disappearing_is_an_engine_change(self):
        base_text = (
            'First = ini.Get_Int(Name(), "Shared", First);\n'
            'Second = ini.Get_Int(Name(), "Shared", Second);\n')
        current_text = 'First = ini.Get_Int(Name(), "Shared", First);\n'
        root = self._tree(current_text)
        base = {"Shared": {"scopes": [scope(applies_to="UnitType")]}}
        current = {"Shared": {"scopes": [scope(applies_to="global rules")]}}

        result = historical_corrections(
            current, base, root, lambda path: base_text)

        self.assertEqual(result, set())


if __name__ == "__main__":
    unittest.main()

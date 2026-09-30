from pathlib import Path
import sys
import tempfile
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import ini_inventory


class RecursiveReaderDiscoveryTests(unittest.TestCase):
    def test_new_nested_read_ini_class_is_discovered_without_manifest_edit(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            source = root / "nested" / "reader.cpp"
            source.parent.mkdir()
            source.write_text(
                'bool NewReader::Read_INI(CCINIClass const & ini) '
                '{ Value = ini.Get_Int(Name(), "NewSetting", Value); return true; }',
                encoding="latin-1",
            )
            units = ini_inventory.discover_read_ini_units(
                root,
                {"version": 1, "reader_exclusions": [], "site_exclusions": []},
                configured=(),
            )
        self.assertEqual(units, [("nested/reader.cpp", "NewReader")])


if __name__ == "__main__":
    unittest.main()

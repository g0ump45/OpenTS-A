import argparse
from contextlib import redirect_stderr
import io
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

import yaml


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import contributor


class CatalogScaffoldTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.manual = self.root / "manual"
        self.data = self.manual / "data"
        self.data.mkdir(parents=True)
        for folder in ("systems", "guides", "using", "formats", "commands"):
            (self.manual / "content" / folder).mkdir(parents=True)
        (self.manual / "changes").mkdir()
        (self.data / "releases.yaml").write_text(
            "releases:\n  - version: 0.2.0\n    status: development\n",
            encoding="utf-8",
        )

    def patches(self):
        return (
            mock.patch.object(contributor, "ROOT", self.root),
            mock.patch.object(contributor, "MANUAL", self.manual),
            mock.patch.object(contributor, "DATA", self.data),
        )

    def test_authored_page_scaffolds_derive_routes_and_required_fields(self):
        with self.patches()[0], self.patches()[1], self.patches()[2]:
            contributor.scaffold_system("rocket-spawners")
            contributor.scaffold_guide("repair-local-data")
            contributor.scaffold_using("preview-status", "getting-started")
            contributor.scaffold_format("packet_log", "binary")

        system = self.manual / "content" / "systems" / "rocket-spawners.md"
        guide = self.manual / "content" / "guides" / "repair-local-data.md"
        using = self.manual / "content" / "using" / "preview-status.md"
        format_page = self.manual / "content" / "formats" / "packet-log.md"
        for path in (system, guide, using, format_page):
            self.assertTrue(path.is_file(), path)

        self.assertIn("keys: []", system.read_text(encoding="utf-8"))
        self.assertIn("prerequisites: []", guide.read_text(encoding="utf-8"))
        self.assertIn("category: getting-started", using.read_text(encoding="utf-8"))
        self.assertIn("format_id: packet_log", format_page.read_text(encoding="utf-8"))
        self.assertIn("kind: binary", format_page.read_text(encoding="utf-8"))

    def test_command_scaffold_requires_an_exact_generated_id(self):
        (self.data / "commands.yaml").write_text(yaml.safe_dump({
            "registered_commands": [{
                "id": "ToggleRadar",
                "route_id": "toggle-radar",
            }],
            "fixed_controls": [],
            "launch_options": [],
        }), encoding="utf-8")
        with self.patches()[0], self.patches()[1], self.patches()[2]:
            contributor.scaffold_command("ToggleRadar")
            with self.assertRaisesRegex(ValueError, "exact case"):
                contributor.scaffold_command("toggleradar")
            with self.assertRaisesRegex(ValueError, "refusing to overwrite"):
                contributor.scaffold_command("ToggleRadar")

        target = self.manual / "content" / "commands" / "toggle-radar.md"
        self.assertIn("command_id: ToggleRadar", target.read_text(encoding="utf-8"))

    def test_parser_enforces_variant_specific_options(self):
        parser = argparse.ArgumentParser()
        commands = parser.add_subparsers(dest="command", required=True)
        contributor.add_parsers(commands)

        for arguments in (
            ["scaffold", "using", "preview-status"],
            ["scaffold", "format", "mix"],
            ["scaffold", "command", "ToggleRadar", "--scope", "global"],
        ):
            parsed = parser.parse_args(arguments)
            with redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                contributor.validate_scaffold_arguments(parser, parsed)

        parsed = parser.parse_args([
            "scaffold", "change", "remove-command",
            "--target-type", "command", "--target-id", "OldCommand",
            "--effect", "removed", "--breaking",
            "--migration", "Remove the obsolete binding from KEYBOARD.INI.",
        ])
        contributor.validate_scaffold_arguments(parser, parsed)


if __name__ == "__main__":
    unittest.main()

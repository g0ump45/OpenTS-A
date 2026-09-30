from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import contributor_engine


def record(name, directory, title, category, release, breaking=False,
           migration=(), credit=()):
    lines = ["---", f"title: {title}", f"category: {category}",
             f"release: {release}"]
    if breaking:
        lines.append("breaking: true")
        lines.append("migration:")
        lines.extend(f"- {step}" for step in migration)
    if credit:
        lines.append("credit: [" + ", ".join(credit) + "]")
    lines += ["---", "", "Body prose.", ""]
    (directory / f"{name}.md").write_text("\n".join(lines), encoding="utf-8")


class ReleaseNotesTests(unittest.TestCase):
    def test_orders_sections_and_appends_credits(self):
        with tempfile.TemporaryDirectory() as temporary:
            manual = Path(temporary)
            changes = manual / "changes"
            changes.mkdir()
            record("b-fix", changes, "Fix the thing", "fix", "0.1.0",
                   credit=("ZivDero", "ts-patches contributors"))
            record("a-feature", changes, "Add the thing", "feature", "0.1.0")
            record("c-breaking", changes, "Break the thing", "feature", "0.1.0",
                   breaking=True, migration=("Rename the key.",))
            record("later", changes, "Future work", "fix", "0.2.0")
            with mock.patch.object(contributor_engine, "MANUAL", manual):
                notes = contributor_engine.release_notes("0.1.0")

        self.assertEqual(notes, "\n".join([
            "### Breaking changes",
            "",
            "- Break the thing",
            "  - Migration: Rename the key.",
            "",
            "### New features",
            "",
            "- Add the thing",
            "- Break the thing",
            "",
            "### Bug fixes",
            "",
            "- Fix the thing (by ZivDero, ts-patches contributors)",
            "",
        ]))

    def test_refuses_a_release_no_record_targets(self):
        with tempfile.TemporaryDirectory() as temporary:
            manual = Path(temporary)
            (manual / "changes").mkdir()
            with mock.patch.object(contributor_engine, "MANUAL", manual):
                with self.assertRaises(ValueError):
                    contributor_engine.release_notes("9.9.9")


if __name__ == "__main__":
    unittest.main()

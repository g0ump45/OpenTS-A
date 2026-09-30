"""Generate the scripting catalog with shared-contract and atomic writes."""

import argparse
import sys

import scripting_engine as _engine
from scripting_engine import *  # noqa: F401,F403 - preserve helper API

from io_utils import atomic_write_text
import schema_validation


def build_catalog():
    _engine.validate_parameter_map()
    actions, orphans = _engine.extract_actions()
    events = _engine.extract_events()
    _engine.validate_example_maps(actions, events)
    missions = _engine.extract_missions()
    data = {
        "trigger_actions": actions,
        "trigger_action_orphan_texts": orphans,
        "trigger_events": events,
        "team_missions": missions,
    }
    errors = schema_validation.errors_for(
        data, "generated-scripting.schema.json", "generated scripting catalog")
    if errors:
        raise ValueError("\n".join(errors))
    return data


def _report(data):
    rows = (
        ("trigger actions", data["trigger_actions"]),
        ("trigger events", data["trigger_events"]),
        ("team missions", data["team_missions"]),
    )
    for label, records in rows:
        named = sum(1 for record in records if record["editor_name"])
        described = sum(1 for record in records if record["editor_description"])
        with_parameters = sum(1 for record in records if record["parameters"])
        flagged = [
            record["id"] for record in records
            if record["status"] in ("needs_label", "needs_review")
        ]
        print(
            f"{label:16s}: {len(records)} total, {named} named, "
            f"{described} described, {with_parameters} with parameters")
        if flagged:
            print(f"{'':18s}flagged: {', '.join(flagged[:8])}")
    orphans = data["trigger_action_orphan_texts"]
    print(
        f"orphan texts    : {len(orphans)} "
        f"({', '.join(repr(row['name']) for row in orphans)})")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out")
    parser.add_argument("--report", action="store_true")
    arguments = parser.parse_args()

    try:
        data = build_catalog()
        if arguments.out:
            payload = _engine.yaml.safe_dump(
                data, sort_keys=False, allow_unicode=True, width=100)
            atomic_write_text(arguments.out, payload)
    except (OSError, ValueError) as error:
        print("ACTION REQUIRED", file=sys.stderr)
        for line in str(error).splitlines():
            print(f"  - {line}", file=sys.stderr)
        return 1

    if arguments.report or not arguments.out:
        _report(data)
    return 0


if __name__ == "__main__":
    sys.exit(main())

"""Generate the command catalog with shared-contract and atomic writes."""

import argparse
import sys

import yaml

import commands_engine
from io_utils import atomic_write_text


def build_catalog():
    return commands_engine.build_catalog()


def report(data):
    release = sum(
        "release" in record["availability"]["builds"]
        for record in data["registered_commands"])
    debug = sum(
        "debug" in record["availability"]["builds"]
        for record in data["registered_commands"])
    print(f"registered commands: {release} Release, {debug} Debug")
    print(f"fixed controls     : {len(data['fixed_controls'])}")
    print(f"launch options     : {len(data['launch_options'])}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out")
    parser.add_argument("--report", action="store_true")
    arguments = parser.parse_args()
    try:
        data = build_catalog()
        if arguments.out:
            payload = yaml.safe_dump(data, sort_keys=False, allow_unicode=True, width=100)
            atomic_write_text(arguments.out, payload)
    except (OSError, ValueError) as error:
        print("ACTION REQUIRED", file=sys.stderr)
        for line in str(error).splitlines():
            print(f"  - {line}", file=sys.stderr)
        return 1
    if arguments.report or not arguments.out:
        report(data)
    return 0


if __name__ == "__main__":
    sys.exit(main())

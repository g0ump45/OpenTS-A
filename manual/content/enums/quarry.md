---
enum_id: QuarryType
slug: quarry
title: Quarry target category
summary: Broad target categories a team attack mission scans for, and that a house records as its preferred target.
representation: integer
bindings:
  key_value_types: []
  scripting_parameter_types: [quarry]
source_files: [code/quarry.hh, code/quarry.cpp, code/team.cpp]
values:
  - { constant: QUARRY_NONE, value: 0, input: "0", meaning: "No category, and no target is assigned." }
  - { constant: QUARRY_ANYTHING, value: 1, input: "1", meaning: "Any suitable enemy." }
  - { constant: QUARRY_BUILDINGS, value: 2, input: "2", meaning: "Buildings in general." }
  - { constant: QUARRY_HARVESTERS, value: 3, input: "3", meaning: "Harvesters or refineries." }
  - { constant: QUARRY_INFANTRY, value: 4, input: "4", meaning: "Infantry." }
  - { constant: QUARRY_VEHICLES, value: 5, input: "5", meaning: "Combat vehicles." }
  - { constant: QUARRY_FACTORIES, value: 6, input: "6", meaning: "Production factories." }
  - { constant: QUARRY_DEFENSE, value: 7, input: "7", meaning: "Base-defense buildings." }
  - { constant: QUARRY_THREAT, value: 8, input: "8", meaning: "Runs the same unrestricted scan as category 1; nothing measures proximity to a base." }
  - { constant: QUARRY_POWER, value: 9, input: "9", meaning: "Power facilities." }
---

A **quarry** is the kind of object a team is hunting rather than any one target it has picked. The category is accordingly a filter on a whole-map scan: a team's attack mission hands it to a member of the team, and [target selection](/systems/target-selection/) decides which candidates that category admits and scores what survives. A value outside the list is treated the same way as category 0 — no target is assigned, and the team is marked ready for its next mission.

The categories have a second consumer that is not a scan at all: [Preferred target...](/mapping/actions/taction-preferred-target/) stores one on a house rather than handing it to a team, and that page covers what becomes of it.

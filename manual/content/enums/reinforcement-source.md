---
enum_id: SourceType
slug: reinforcement-source
title: Reinforcement source
summary: Map-edge and air origins used when objects cross a scenario's boundary.
representation: token
bindings:
  key_value_types: [sourcetype]
  scripting_parameter_types: []
source_files: [code/source.hh, code/_source.cpp, code/display.cpp, code/reinf.cpp]
values:
  - { constant: SOURCE_NORTH, value: 0, input: "North", meaning: "Enter from the north edge." }
  - { constant: SOURCE_EAST, value: 1, input: "East", meaning: "Enter from the east edge." }
  - { constant: SOURCE_SOUTH, value: 2, input: "South", meaning: "Enter from the south edge." }
  - { constant: SOURCE_WEST, value: 3, input: "West", meaning: "Enter from the west edge." }
  - { constant: SOURCE_AIR, value: 4, input: "Air", meaning: "Arrive by air rather than a map edge." }
---

Only four of the five name a boundary: `Air` describes how something arrives rather than where, and the routine that turns a source into a cell to scan along has a case for those four alone. [`Edge`](/keys/edge/) covers what each route does with the source a house holds.

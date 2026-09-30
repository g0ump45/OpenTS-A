---
format_id: taskforces
title: Task forces
summary: Registers reusable team compositions containing up to six infantry, vehicle, or aircraft entries.
kind: record
route: /mapping/task-forces/
files:
  - AI.INI
  - AIFS.INI
  - map file
section: TaskForces
syntax: "<slot>=<count>,<ObjectType ID>"
registration: { section: TaskForces, id_from: value, entry_section: "<TaskForce ID>" }
fields:
  - { position: 1, label: Count, value: Integer unit count, required: true }
  - { position: 2, label: Type, value: "InfantryType, UnitType, or AircraftType ID", required: true }
key_scopes:
  - applies_to: TaskForce
source_files:
  - code/taskforc.cpp
  - code/emember.cpp
  - code/init.cpp
  - code/scenario.cpp
---

`[TaskForces]` values name the TaskForce sections to load. Each TaskForce section accepts numbered member lines `0` through `5`.

OpenTS loads `AI.INI`, then `AIFS.INI` when Firestorm is enabled, then the map-local definitions.

```ini title="AI.INI, AIFS.INI, or map file"
[TaskForces]
0=MyAttackForce

[MyAttackForce]
Name=Attack force
0=4,E1
1=1,MMCH
```

A member type is resolved as infantry, vehicle, then aircraft. Buildings are not accepted. An unresolved member is dropped; surviving members are packed together, so gaps in the numbered slots collapse.

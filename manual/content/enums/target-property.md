---
enum_id: TargetPropertyType
slug: target-property
title: Target property
summary: Selection rules used when a team script picks one building from all those of a named type.
representation: integer
bindings:
  key_value_types: []
  scripting_parameter_types: [target-property]
source_files: [code/target.hh, code/team.cpp, code/map.cpp]
values:
  - { constant: TPROPERTY_LEAST_THREAT, value: 0, input: "0", meaning: "Pick the candidate standing in the map region the team's house rates as least threatened." }
  - { constant: TPROPERTY_GREATEST_THREAT, value: 1, input: "1", meaning: "Pick the candidate standing in the map region the team's house rates as most threatened." }
  - { constant: TPROPERTY_NEAREST, value: 2, input: "2", meaning: "Pick the candidate nearest the team's first member." }
  - { constant: TPROPERTY_FARTHEST, value: 3, input: "3", meaning: "Pick the candidate farthest from the team's first member." }
---

The two threat properties do not weigh the building. They read a running figure the team member's own house keeps for each **map region** — a four-by-four block of cells, the unit the whole threat map is kept in — so `Least threat` heads for the quietest part of the map holding a building of that type and `Greatest threat` for the busiest, and neither has anything to say about how dangerous the building itself is.

That figure is neither confined to the region it is filed under nor a measure of hostile force alone. An object raising it writes across a three-by-three block of regions: its full **risk**, which is its type's [`ThreatPosed`](/keys/threatposed/), in the region it stands in, half of that in the four regions beside it and a quarter in the four corners, so every reading is smeared across a neighborhood.

Whose figures an object raises is settled by one test, applied as it is placed, as it crosses from one region into another, as its owner changes and as it is taken off the map. The table gives the four positions a house can hold toward the object's owner. Only one kind of ally is spared, which is the point: an alliance protects a human house from its ally's risk and does nothing for a computer one.

| The house keeping the figure | Is the object's risk added to it? |
| --- | --- |
| The object's own owner | No |
| A human house allied to the owner | No |
| A computer house allied to the owner | Yes |
| Any house not allied to the owner | Yes |

The rebuild a house runs whenever it makes or breaks an alliance applies that test to infantry, vehicles and aircraft alone. Everything else it counts, structures included, is added with no ownership or alliance test at all, so from that point the house's own structures raise its own figures.

A value outside the four scores every candidate identically and therefore selects none, which leaves the team with no target and sends it on to the next line of its script.

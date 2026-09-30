---
key: SmallVisceroid
scope: global-rules
label: Spawned visceroid type
see_also: ["TiberiumDeathToVisceroid", "LargeVisceroid", "system:tiberium"]
when_omitted:
  kind: value
  value: none
---

The named UnitType is the creature Tiberium leaves behind, and it is created for the Neutral house rather than for whoever owned the victim. Two deaths reach it, both only while the scenario declares [`TiberiumDeathToVisceroid=yes`](/keys/tiberiumdeathtovisceroid/): an infantryman killed by the Tiberium under its feet, and any object killed by a damaging particle. In each case the new creature appears on the cell the death happened in, and is left uncreated if a vehicle already occupies that cell.

[Damage](/systems/tiberium/#damage) covers the hit that produces the first of those deaths.

The name here does not have to belong to a declared UnitType. A name that matches nothing does not resolve to no type; a UnitType of that name is brought into existence instead, configured by a section of the same name if the rules go on to supply one and left blank if they do not. The literals `none` and `<none>` are the exception: those do resolve to no type.

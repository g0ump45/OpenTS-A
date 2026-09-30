---
key: Cloakable
summary: Whether an object of this type hides itself and recovers its cloak on its own.
see_also: ["system:cloaking"]
when_omitted:
  kind: value
  value: "no"
---

The value is copied onto each object as it is created, and every later test reads that copy rather than the type, so the ability can be handed out during a match: a [cloak crate](/keys/crateradius/) sets the copy on every object standing near it, whatever house owns it.

A cloakable object hides itself whenever nothing on the [list of refusals](/systems/cloaking/#starting-a-cloak) applies, and it starts hiding again after every event that forces it out. An object without the flag can still be hidden — by a [cloaking field](/systems/cloaking/#cloaking-fields) covering its cell, or by the `CLOAK` [veteran ability](/systems/veterancy/#abilities) — but it stays hidden only as long as that cover lasts.

:::caution[An AircraftType never receives the copy]
The copy onto the object is made for UnitTypes, InfantryTypes and BuildingTypes. An AircraftType has no such step, so `Cloakable=yes` in an aircraft section grants nothing; a cloaking field, a cloak crate, and the cloak ability remain the only ways an aircraft disappears.
:::

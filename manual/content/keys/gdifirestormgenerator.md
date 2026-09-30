---
key: GDIFirestormGenerator
summary: The BuildingType whose loss discharges a house's firestorm superweapon and brings down its wall.
see_also: [FirestormWall, "system:laser-fences", "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

A structure of exactly this type being taken off the map or switched off makes its house recount, and only while its wall is up. If nothing of this type remains that is switched on, out of limbo, and neither being built nor deconstructed, every [`Type=Firestorm`](/keys/type/) weapon the house holds is [discharged](/systems/superweapons/#the-firestorm-defense) and the wall comes down. For a house under human control that is the same discharge a second cameo click performs, so the drain the wall had not yet spent is turned back into charge.

The test names one type outright rather than asking which structure granted the weapon; [losing the generator](/systems/laser-fences/#losing-the-generator) covers what that means for a rules set that grants the defense from somewhere else.

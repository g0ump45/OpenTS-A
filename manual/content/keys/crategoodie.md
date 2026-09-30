---
key: CrateGoodie
summary: Whether the vehicle type is in the random pool a unit crate draws from.
see_also: ["system:crates"]
when_omitted:
  kind: value
  value: "no"
---

The draw is reached only when [`UnitCrateType`](/keys/unitcratetype/) names nothing and neither free-vehicle rescue applies. It then picks registered UnitTypes at random and keeps the first that carries this flag, is ownable by the collector's house, and — for the [`BaseUnit`](/keys/baseunit/) type — is being drawn in a match with bases enabled.

:::danger[The draw has no exit for an empty pool]
The random pick repeats until it finds an acceptable type and has no attempt limit. A house that owns no `CrateGoodie=yes` vehicle type at all, whether because none carries the flag or because none is ownable by that house, leaves the draw with nothing to find and the game stops responding at that pickup. Naming any type in `UnitCrateType` avoids the draw entirely.
:::

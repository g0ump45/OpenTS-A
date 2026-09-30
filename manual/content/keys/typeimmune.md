---
key: TypeImmune
summary: Stops an object taking damage from another object of exactly its own type and house.
see_also: [Immune, Armor, VeteranArmor]
when_omitted:
  kind: value
  value: "no"
---

```ini title="rules.ini"
[MYARTILLERY] ; a UnitType registered in [VehicleTypes]
TypeImmune=yes
```

The test is a pair of exact matches — the attacker's type is the same type, and the attacker's house is the same house — so allied fire from a different house still lands, and so does fire from a different type however similar. It is what keeps a line of artillery from shredding itself on its own splash.

The check sits at the top of the damage path, after the armor biases and the veteran armor bonus have been applied but before any of the damage is dealt. A blocked hit is reported as no damage at all, so nothing downstream of it happens either: no strength is lost, the target does not turn on the shooter, and the shooter's house earns no anger from its owner.

Only ordinary positive damage is filtered. Damage delivered as forced — a demolition charge going off, a crushing, the engine finishing off an object outright — passes through whatever this setting says, and so does healing.

---
key: FlameDamage
summary: The warhead a napalm crate's blast carries.
see_also: ["FlameDamage2", "C4Warhead", "system:crates"]
when_omitted:
  kind: value
  value: none
---

One thing reads it: the napalm result of a pickup crate. The unit that collected the crate is hit directly through this warhead, and a blast of the same damage goes off at the midpoint between the crate's cell and the collector, also through it. [Crates](/systems/crates/) covers the result and where its damage figure comes from.

Nothing that burns during ordinary play uses it. The damage a fire, flame or other damaging animation deals as it plays goes through [`FlameDamage2`](/keys/flamedamage2/) instead.

Leaving it unset costs the result its blast — a detonation with no warhead is abandoned before anything is damaged — but not the direct hit, which is forced damage and lands at its full figure regardless of warhead or armor.

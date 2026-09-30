---
key: Proximity
summary: Parsed flag that the engine never uses.
no_effect: true
see_also: [Arm, ROT]
when_omitted:
  kind: value
  value: "no"
---

The name promises a projectile that goes off when it passes near its target rather than only on a direct hit. That behavior exists, but it is not gated by this flag: every projectile steered by the homing flight model runs the proximity trip, and clearing the flag exempts nothing. [`Arm`](/keys/arm/) is what holds that trip shut, and [`ROT`](/keys/rot/#scope-bullettype) is what decides whether it runs at all.

No gameplay path reads the stored flag.

---
key: MissileROTVar
summary: How far a homing projectile's rate of turn swings above its nominal value.
see_also: [MissileSpeedVar, ROT]
when_omitted:
  kind: value
  value: ".25"
---

A projectile with a [`ROT`](/keys/rot/#scope-bullettype) above zero is steered by the homing flight model, and this figure is what makes it weave rather than track straight. The rate of turn is scaled by a factor swinging over a fifteen-frame cycle, from `1` at the bottom of the cycle to `1` plus twice this figure at the top, so the swing is entirely above the nominal rate — a value of `0` gives a straight approach and never a slower turn.

Each projectile enters the cycle at its own point, so missiles launched together do not weave in step.

Two other adjustments sit outside the cycle: a projectile still working up to speed after launch is given no turn at all, and one within a cell of its target turns half again as fast as the cycle asks.

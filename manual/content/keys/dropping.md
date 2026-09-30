---
key: Dropping
summary: Marks the projectile as a bomb that falls from a height rather than flying to its target.
see_also: [ROT, Arm]
when_omitted:
  kind: value
  value: "no"
---

The setting changes the launch and the fuse. The projectile is released along the firer's own heading rather than toward the target, exactly as a homing projectile is, and the firing sound is played from the firer's center instead of from the barrel. It then ignores its fuse completely: the proximity trip that ends an ordinary flight is never consulted, so nothing about [`Arm`](/keys/arm/) or the distance to the target applies.

:::caution[A dropping projectile detonates on its first logic frame]
Detonation is forced as soon as the projectile is not falling, and no path in the engine ever sets a projectile falling. The shot therefore goes off one frame's travel from where it was released, whatever else the section says.
:::

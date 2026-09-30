---
key: EMEffect
summary: Makes the warhead's detonation create an EM pulse instead of applying blast damage.
see_also: ["system:emp-pulse"]
when_omitted:
  kind: value
  value: "no"
---

A projectile carrying such a warhead skips the fuse and proximity adjustments of an ordinary shot — though one ending within 32 leptons of its target still snaps to the target's center — and [creates a pulse](/systems/emp-pulse/#firing-a-pulse) whose radius is the warhead's [`Spread`](/keys/spread/) and whose duration is the weapon's [`Damage`](/keys/damage/). The impact animation is drawn at random from the warhead's [`AnimList`](/keys/animlist/) instead of being selected by damage, so every entry of that list can appear rather than only the one the damage bracket selects.

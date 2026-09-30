---
key: Degenerates
summary: Bleeds a point of damage off the projectile for every game frame it stays in flight.
see_also: [Damage, Ranged]
when_omitted:
  kind: value
  value: "no"
---

The loss is applied once on each logic frame the projectile spends still flying, and it stops at `5`: a projectile can never be worn below five points of damage this way. At 15 game frames to the second, a shot launched with 100 damage is down to the floor after about six and a half seconds of flight.

What decays is the damage figure the shot was launched with, after the firer's firepower bonuses were applied to the weapon's [`Damage`](/keys/damage/#scope-weapontype). The weapon itself is untouched, so the next shot starts from full again.

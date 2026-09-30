---
key: EMPulseProjectile
summary: Parsed BulletType that the engine never uses.
no_effect: true
see_also: [EMPulseWarhead, EMPulseCannon, "system:emp-pulse"]
when_omitted:
  kind: value
  value: none
---

The name promises the projectile an EM pulse cannon launches. [Firing the cannon](/systems/emp-pulse/#em-pulse-cannon-superweapon) instead fires the building's own primary weapon, so the shot takes that weapon's [`Projectile=`](/keys/projectile/). Nothing beyond the save file and the cleanup that clears the pointer when a projectile type is deleted touches the value stored here.

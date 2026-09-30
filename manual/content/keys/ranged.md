---
key: Ranged
summary: Gives the projectile a fuel supply, detonating it once it has flown the firing weapon's projectile range.
see_also: [ProjectileRange, Range, Arm]
when_omitted:
  kind: value
  value: "no"
---

The distance the projectile covers each game frame is taken off its remaining allowance, and it detonates wherever it happens to be when the allowance runs out. Both flight models spend fuel the same way.

The allowance is the firing weapon's [`ProjectileRange`](/keys/projectilerange/) and not its [`Range`](/keys/range/). Those are separate settings: `Range` is how far the weapon may be fired, `ProjectileRange` is how far the shot may then travel. A weapon that never narrows `ProjectileRange` gives its projectile roughly 390 cells to spend, so marking the projectile fueled without also setting `ProjectileRange` leaves it flying effectively without limit. A bomblet released by a [`Splits=yes`](/keys/splits/) projectile works the other way round: it is given its [`AirburstWeapon`](/keys/airburstweapon/)'s `Range` as the allowance.

```ini title="rules.ini"
[MYROCKET] ; a BulletType, registered by a weapon naming it as its Projectile
Image=MISSILE
ROT=5
Ranged=yes

[MyRocketLauncher] ; a WeaponType, registered by an object naming it as its Primary
Projectile=MYROCKET
Range=7
ProjectileRange=9 ; two cells of chase beyond the range it may be fired at
```

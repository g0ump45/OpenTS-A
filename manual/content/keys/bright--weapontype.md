---
key: Bright
scope: weapontype
label: Weapon flash
when_omitted:
  kind: value
  value: "no"
---

Every shot the weapon fires carries the flag with it, and a shot that carries it lights the ground where it lands, whatever the shot did or failed to do on arrival. The flash is a spotlight sized at a quarter of the damage the shot delivered, rounded down and held between 21 and 63: anything up to 87 damage gives the smallest flash, anything from 252 up gives the largest.

```ini title="rules.ini"
[MyCannon] ; example WeaponType
Damage=400
Bright=yes ; the impact lights the surrounding ground
```

:::caution[A projectile impact never consults the warhead's flag]
The [warhead's own](/keys/bright/#scope-warheadtype) `Bright=` is not read when a shot lands. It governs the explosions staged without a projectile instead, which that page describes. A warhead marked bright therefore leaves every shot that carries it unlit unless the weapon is marked too.
:::

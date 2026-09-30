---
key: Bright
scope: warheadtype
label: Explosion flash
see_also: [Explodes, IonStormWarhead, IonCannonWarhead, C4Warhead]
when_omitted:
  kind: value
  value: "no"
---

The explosion drops a spotlight over the ground around it. Its size is a quarter of the damage, rounded down and held between 21 and 63, so any blast of 87 damage or less produces the smallest flash and any blast of 252 or more the largest; the light widens for its first two frames and then shrinks away over the eight that follow.

```ini title="rules.ini"
[MyShellWH] ; example WarheadType
Bright=yes
```

The explosions that read the flag are the ones raised without a projectile: an animation or voxel animation that detonates as it expires, the collateral blast an [`Explodes=yes`](/keys/explodes/#scope-aircrafttype) object makes when it is destroyed, [`IonStormWarhead`](/keys/ionstormwarhead/) lightning, [`IonCannonWarhead`](/keys/ioncannonwarhead/), the [Do Explosion At](/mapping/actions/taction-do-explosion/) trigger action, and everything the [`C4Warhead`](/keys/c4warhead/) stages — a laser fence segment blown up with its post, a vehicle stranded and blowing itself up, an object that falls out of the sky, an explosive crate, a hunter-seeker, and the three lighting trigger actions. A shot that lands takes its flash from [the firing weapon's own flag](/keys/bright/#scope-weapontype) instead and never consults this one.

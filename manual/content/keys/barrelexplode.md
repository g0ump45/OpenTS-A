---
key: BarrelExplode
summary: The explosion animation played where an exploding overlay is set off.
see_also: [AmmoCrateDamage, BarrelDebris, BarrelParticle, Explodes]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
BarrelExplode=MYBARRELBOOM ; an AnimType registered in [Animations]
```

The animation is created at the coordinate handed to the blast, a point inside the cell the overlay stood in rather than its center, before the blast itself is applied. It is the same one for every exploding overlay: an overlay type cannot name its own. [`AmmoCrateDamage`](/keys/ammocratedamage/) covers the damage, the debris and the fires that follow it.

The neighboring cells that catch light from the blast do not use this animation; the engine names that fire for itself.

:::danger[An unset animation crashes the game at the first barrel]
The explosion is created without first checking that an animation was named, so with the key unset the game crashes the first time anything sets off an [`Explodes=yes`](/keys/explodes/#scope-overlaytype) overlay.
:::

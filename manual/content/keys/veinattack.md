---
key: VeinAttack
summary: AnimType a vein cell attaches to itself to hurt what stands in it.
see_also: ["system:veins", "IsVeins", "VeinDamage", "VeinholeWarhead"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
VeinAttack=VEINATAC
```

The animation is the whole of the [vein attack](/systems/veins/#standing-in-veins): a cell of mature, flat vein creates one over itself as soon as a vulnerable object is in it, and the animation applies the damage on every other frame until it removes itself. A cell takes no new attack while one is already attached to it, but a single trigger creates one animation for every vulnerable object standing there at that moment, and each of them deals the full damage — so a cell holding three vulnerable infantry damages everything in it three times over.

:::danger[An unresolved setting faults the first time veins ripen]
This setting has no built-in value, and the cell creates the animation without checking what it got. With the setting unresolved, the first time a vulnerable object and mature flat vein meet in the same cell — whether the object arrives or the vein ripens under it — the cell builds an animation from a null type and faults. The named animation must also carry [`IsVeins=yes`](/keys/isveins/#scope-animtype) in `art.ini`, or it plays as ordinary artwork and permanently blocks its cell from attacking again.
:::

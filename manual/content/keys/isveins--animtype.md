---
key: IsVeins
scope: animtype
label: Vein attack animation
see_also: ["system:veins", "VeinAttack", "VeinDamage"]
when_omitted:
  kind: value
  value: "no"
---

```ini title="art.ini"
[VEINATAC] ; the AnimType named by [AudioVisual] VeinAttack
IsVeins=true
```

The flag, not the [`VeinAttack`](/keys/veinattack/) setting, is what gives an animation the [vein attack behavior](/systems/veins/#standing-in-veins): it deals [`VeinDamage`](/keys/veindamage/) to every live unit, structure or infantryman standing in its cell on every other frame, and being taken off the map releases the cell so that a later object can set the attack off again. The animation is also drawn in the local player's color scheme.

:::caution[The animation named by VeinAttack needs the flag]
An animation used as `VeinAttack` without the flag plays as ordinary artwork, deals no damage, and never releases the cell it was attached to, so that cell cannot start another attack for the rest of the scenario.
:::

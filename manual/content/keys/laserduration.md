---
key: LaserDuration
summary: How many frames a laser beam stays drawn for.
see_also: ["IsLaser", "IsBigLaser"]
when_omitted:
  kind: value
  value: "10"
---

The beam advances one stage each frame and is taken off the screen once it reaches this figure, so the value is a lifetime in game frames — fifteen to the second. It governs only the colored line; the screen glow that accompanies a laser shot fades on its own fixed schedule of about 22 frames.

```ini title="rules.ini"
[MyObeliskRay] ; example WeaponType
IsLaser=yes
LaserDuration=15 ; one second
```

Like the rest of the beam settings, the figure is taken from the weapon in the object's first slot whichever slot actually fired.

:::caution[The value is stored in a single signed byte]
Only the low eight bits survive, read as a signed number. `LaserDuration=127` is the longest beam that can be asked for; `128` through `255` land below zero and `256` lands on zero, and a figure of zero or less puts the beam on screen for a single frame before it is removed.
:::

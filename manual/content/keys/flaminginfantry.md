---
key: FlamingInfantry
summary: The burning figure left where fire kills an infantryman.
see_also: [InfDeath, Doggie, IsFlamingGuy, RunningFrames, SmallFire]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
FlamingInfantry=MYFLAMEGUY ; an AnimType registered in [Animations]
```

A warhead carrying [`InfDeath=4`](/keys/infdeath/) that kills an infantryman replaces the corpse with this animation at his position and deletes the soldier outright, so nothing of him is left to be crushed, shot or targeted. A [`Doggie=yes`](/keys/doggie/) infantryman takes its own fire-death sequence instead. Three earlier branches also take precedence over the warhead's choice: a soldier who was already falling and comes down within ten leptons of water splashes instead, a prone [`Cyborg=yes`](/keys/cyborg/) infantryman and a jumpjet infantryman both take [`InfantryExplode`](/keys/infantryexplode/).

The staggering about is the animation's own behavior, not this setting's. [`IsFlamingGuy=yes`](/keys/isflamingguy/) on the named type is what makes it run from cell to cell for up to seven steps before collapsing, and [`RunningFrames`](/keys/runningframes/) sizes the sequence it collapses into. Naming a type without that flag simply plays the animation where the soldier fell.

:::caution[The burning figure always wears the local player's colors]
Its remap is set from the local player's color scheme as it is created, whichever house owned the soldier, and every burning figure on the map is repainted the same way when a saved game is loaded. Two players watching the same death see it in two different colors.
:::

:::danger[An unset animation crashes the game when `InfDeath=4` kills a soldier that is not a dog]
The figure is created without first checking that a type was named, so with the key unset the game crashes the first time a warhead with `InfDeath=4` kills a soldier who is not a dog.
:::

---
key: TrailerAnim
scope: animtype
label: Animation trail
see_also: ["TrailerSeperation", "Bouncer", "IsMeteor"]
when_omitted:
  kind: value
  value: none
---

An animation of the named type is created at the animation's position for as long as it is alive, on every frame of the game clock whose number is a multiple of [`TrailerSeperation`](/keys/trailerseperation/). The count is the clock's rather than the animation's own, so every animation of the type sheds its trail on the same frames, and a trailer begins one frame after it is created.

Nothing restricts this to thrown animations. An explosion or a smoke column that names a trailer sheds one just as a meteor does.

A value naming no registered animation is not refused: a type of that name is created on the spot, holding no artwork and every setting at its built-in value.

:::danger[A trail without a separation stops the game]
`TrailerSeperation` is `0` unless the section sets it, and the frame test divides by it. Naming a trailer animation without also giving a separation faults on the animation's first logic frame, so the game stops the moment an animation of the type is created.
:::

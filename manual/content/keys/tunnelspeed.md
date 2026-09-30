---
key: TunnelSpeed
summary: Multiplier on how fast a subterranean unit sinks and rises, and divisor of its dig-in wait.
see_also: [ROT, MovementZone, AllowShroudedSubteranneanMoves]
when_omitted:
  kind: value
  value: "1"
---

Two parts of a dig read this value. Once a unit whose [`Locomotor`](/keys/locomotor/) tunnels has turned to face its destination it waits `(64 ÷ ROT) ÷ TunnelSpeed` frames on its nose before it starts down, so a larger figure shortens the pause. The descent and the ascent then move it its full travel speed times this value, in leptons of height, each frame.

Nothing else in the dig consults it. A unit under the ground advances a fixed 19 leptons a frame toward its destination however this is set, and the wait it serves while righting itself on the surface is `64 ÷ ROT` frames undivided. Raising the value shortens the dig-in and the two vertical legs and leaves the length of the underground crossing exactly as it was.

:::caution[The vertical rate has a floor]
A descent or ascent of fewer than five leptons a frame is raised to five. Lowering this value therefore cannot stall a dig, and once a unit's travel speed times the value falls under that floor, lowering it further changes nothing. `0` is the exception: the dig-in timer divides by this figure, so a zero divides by zero.
:::

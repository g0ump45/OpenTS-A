---
key: WalkRate
summary: The number of game frames each step of a vehicle's walk cycle holds for.
when_omitted:
  kind: value
  value: "1"
---

Every object keeps a running count of animation steps taken, and that count advances by one whenever its locomotor reports that it is moving and the game frame number divides evenly by this figure. The count is what indexes a vehicle's motion — the voxel motion frames of a mech, the walk frames of a shape-drawn vehicle, and the phase of the harvesting animation. Nothing reads the resulting count for infantry or aircraft, whose animation is paced elsewhere.

A larger figure holds each step longer, so the stock Titan's `WalkRate=2` strides at half the frame rate and the Core Defender's `WalkRate=4` at a quarter. Because the test is against the game frame counter rather than a counter of the object's own, every object sharing a figure steps in unison.

:::danger[A figure of zero divides by zero]
The frame counter is divided by this figure once per frame for every moving object on the map, with no guard. Writing `WalkRate=0` therefore brings the game down the moment an object of that type starts to move, whether or not anything draws its walk cycle.
:::

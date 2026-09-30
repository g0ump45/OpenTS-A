---
key: WindEffect
summary: How strongly the prevailing wind carries a particle sideways.
see_also: ["BehavesLike", "Velocity", "WindDirection"]
when_omitted:
  kind: value
  value: "0"
---

The wind pushes a particle by a fixed step of at most two leptons on each axis, in the direction [`WindDirection`](/keys/winddirection/) names. What this figure changes is either how often that step lands or how large it is, and which of the two depends on the [behavior](/keys/behaveslike/#scope-particletype).

`Gas` and `WeakGas` particles take the step on one frame in ten divided by this figure, rounded down, so the scale is coarse and saturates quickly:

| Value | Step applied |
| --- | --- |
| `0` or less | never |
| `1` | one frame in ten |
| `2` | one frame in five |
| `3` | one frame in three |
| `4` or `5` | every other frame |
| `6` through `10` | every frame |

`Smoke` particles work the other way: the step lands every frame and is multiplied by this figure instead, so the drift scales without any ceiling, and a negative value carries the puff upwind. `Fire`, `Spark`, `Railgun` and `Web` particles ignore the setting entirely.

:::danger[Above 10 on a gas particle the game stops]
The interval for `Gas` and `WeakGas` particles is ten divided by this figure in whole numbers, and at `11` or more that division yields zero. The frame counter is then divided by zero and the game stops as soon as a particle of the type moves. Only those two behaviors are exposed: the `Smoke` path multiplies by the figure rather than dividing by it, and takes any value.
:::

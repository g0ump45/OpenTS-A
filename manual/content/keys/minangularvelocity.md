---
key: MinAngularVelocity
summary: The bottom of the range a voxel animation's tumbling rate is drawn from, in degrees per frame.
see_also: ["MaxAngularVelocity", "Duration"]
when_omitted:
  kind: value
  value: "-1"
---

Degrees per frame, converted to radians as it is read. A piece is given one tumbling rate for the whole of its life, drawn once when it is created, and in practice that rate is this figure: the pick that would raise it is quantized in whole radians, so it contributes nothing until [`MaxAngularVelocity`](/keys/maxangularvelocity/) stands about 57 degrees above this setting.

A value of exactly `0` is discarded rather than stored: the rate already held stands, which for a type no earlier file touched is zero as well.

:::danger[A minimum written without a maximum usually crashes the game]
An unwritten [`MaxAngularVelocity`](/keys/maxangularvelocity/) leaves minus one degree per frame stored rather than the built-in ten. A section that writes this key and not that one therefore leaves a maximum below its minimum, and the divisor the pick uses — the truncated whole number of radians between the two, plus one — comes out zero for any minimum above minus one degree and below about 113.5. The division faults, and the game stops the moment a piece of the type is created. Only writing both settings, or neither, avoids it.
:::

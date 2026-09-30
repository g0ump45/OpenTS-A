---
key: TargetDistanceCoefficientDefault
summary: The TargetDistanceCoefficient every object type falls back on.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "0"
---

The value is substituted whenever a type's own [`TargetDistanceCoefficient`](/keys/targetdistancecoefficient/) is zero and the section being read omits the key. An explicit `0` in a section survives its own pass; it is replaced only when a later rules layer carries the section without the key. `[General]` is read before the object types in each pass over the rules, so a value written here reaches every type in the same file.

A positive value here rewards distance rather than penalizing it on every type at once, so a rules-wide distance penalty is written as a negative number.

---
key: SurvivorDivisor
summary: The divisor applied to a structure's cost when its number of survivors is worked out.
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: "100"
---

The count is the structure's cost multiplied by [`SurvivorRate`](/keys/survivorrate/) and divided by this figure, then clamped to between 1 and 5. A structure therefore yields roughly one survivor per hundred credits of half its cost before the clamp bites.

A structure that has [changed hands](/systems/capture/#what-changes-hands) doubles the divisor, halving its count for the rest of the match. A value of `0` is checked before the division and produces no survivors rather than a division by zero.

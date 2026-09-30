---
key: BestLowPowerBuildRateCoefficient
summary: Parsed best-case low-power build coefficient that the engine never uses.
no_effect: true
see_also: ["system:power"]
when_omitted:
  kind: value
  value: ".75"
---

The gentlest production multiplier a shortfall can impose is fixed in the engine at the same `0.75` this default names, and nothing reads the value; changing it does not move that step. [The production ladder](/systems/power/#production) lists the steps that are actually applied.

---
key: WorstLowPowerBuildRateCoefficient
summary: Parsed worst-case low-power build coefficient that the engine never uses.
no_effect: true
see_also: ["system:power"]
when_omitted:
  kind: value
  value: ".3"
---

The worst production multiplier a shortfall can impose is fixed in the engine and floored by [`MinProductionSpeed`](/keys/minproductionspeed/); nothing reads this value. [The production ladder](/systems/power/#production) lists the steps that are actually applied.

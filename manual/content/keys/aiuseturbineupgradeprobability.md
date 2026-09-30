---
key: AIUseTurbineUpgradeProbability
summary: The chance that a computer house named "GDI" answers a power shortfall with a turbine upgrade rather than another power plant.
see_also: ["system:ai-base-building"]
when_omitted:
  kind: value
  value: "1"
---

The value is a fraction of 1, drawn afresh each time [a power shortfall is answered](/systems/ai-base-building/#power-and-money-interventions) and only while the house owns a [`GDIPowerPlant`](/keys/gdipowerplant/) with a free upgrade slot. At `1` the draw effectively always succeeds, so the turbine is taken whenever a slot is free.

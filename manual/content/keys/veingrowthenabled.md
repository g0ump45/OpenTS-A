---
key: VeinGrowthEnabled
summary: Allows veinhole monsters to spread their fields during a scenario.
see_also: ["system:veins", "MaxVeinholeGrowth", "VeinholeGrowthRate"]
when_omitted:
  kind: value
  value: "yes"
---

```ini title="map file"
[Basic]
VeinGrowthEnabled=no
```

The switch is the last clause of the test every monster runs before a [growth step](/systems/veins/#growth), so with it off no field advances by a single cell. Everything else the system does carries on: fields already on the map stay where they are, they still damage what stands in them, they are still harvested, and a destroyed monster's field still withers, since withering is not gated by this switch. The [Vein growth](/mapping/actions/taction-vein-growth/) trigger action writes the same switch while the scenario is running.

---
key: VeinholeShrinkRate
summary: Game frames between the withering steps of a destroyed monster's field.
see_also: ["system:veins", "VeinholeGrowthRate"]
when_omitted:
  kind: value
  value: "100"
---

The timer that paced a monster's growth is reloaded from this figure instead once the monster is [destroyed](/systems/veins/#destruction), with a random extra of up to half of it. Each step takes one ripeness step off 1 to 4 of the cells the monster owned, farthest from the veinhole first, and the monster is disposed of once it has none left. Withering runs whether or not [`VeinGrowthEnabled`](/keys/veingrowthenabled/) is on, so this figure decides how long a killed field lingers.

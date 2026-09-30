---
key: VeinholeGrowthRate
summary: Game frames between one veinhole monster's growth steps.
see_also: ["system:veins", "VeinholeShrinkRate", "MaxVeinholeGrowth"]
when_omitted:
  kind: value
  value: "100"
---

A monster's first step falls due exactly this many frames after it is created. Every step after that reloads the timer with this figure plus a random extra of up to half of it, so steps land between this interval and one and a half times it. One step covers 1 to 5 cells, and the [growth step](/systems/veins/#growth) itself decides whether any of them can be taken, so a short interval spreads a field faster only while there is room under [`MaxVeinholeGrowth`](/keys/maxveinholegrowth/) and ground the field accepts.

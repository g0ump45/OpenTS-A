---
key: WeedCapacity
summary: Units of weed a house can hold.
see_also: ["system:veins", "Weeder", "Storage"]
when_omitted:
  kind: value
  value: "0"
---

```ini title="rules.ini"
[General]
WeedCapacity=56
```

One figure covers every house. A weeder handing its load over adds units one at a time until the house holds this many and throws the rest away, and the [weed pool](/systems/veins/#the-weed-pool) is never converted to credits at any point. The figure also bounds the pip gauge a [`Weeder=yes`](/keys/weeder/#scope-buildingtype) building draws, which shows the house's pool rather than the building's own contents.

:::caution[The pool must be exactly full to be worth anything]
The chemical missile superweapon is the pool's only consumer, and it draws on the pool only while the house holds exactly this many units. Anything less charges nothing, and a recharge empties the pool outright rather than deducting a price.
:::

:::caution[At zero the store holds nothing]
`0` is the figure in force when no rules file sets it. The store compares the house's holdings against it before taking each unit, so at `0` it refuses the first unit offered: a weeder loads, drives home, unloads, and the pool stays empty.
:::

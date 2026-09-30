---
key: AIAlternateProductionCreditCutoff
summary: Credit total below which a computer house builds structures and units in alternation instead of together.
see_also: ["system:ai-base-building", "system:production"]
when_omitted:
  kind: value
  value: "1000"
---

The figure is compared against the house's loose credits plus the value of the Tiberium it holds in storage, and the comparison is made again every time one of the house's factories delivers something.

At or above the figure the house orders structures, vehicles, infantry and aircraft in the same pass. Below it the house drops to one class at a time and turns away from whatever it just delivered: after a structure — or as soon as it has none pending that an owned factory can produce — it moves to units, and after a unit it moves back to structures only when it owns none of the [`BuildBarracks`](/keys/buildbarracks/) types, owns none of the [`BuildWeapons`](/keys/buildweapons/) types, is [drawing more power than it makes](/systems/power/), or wins a one-in-two draw.

The narrowed pass is not a hard block. A house restricted to structures falls through to units as soon as no owned factory can produce the structure it wants, and a house restricted to units falls through to structures once it has nothing pending or nothing pending that an owned factory can produce. While the pending vehicle is the first [`HarvesterUnit`](/keys/harvesterunit/) entry, that restricted house skips infantry and aircraft entirely. [Choosing what to build next](/systems/ai-base-building/#choosing-what-to-build-next) covers how the structure half of the pass picks its target.

:::note[Campaign games never narrow the pass]
The mode is only ever moved in a skirmish or multiplayer game, and the pass ignores it outright in a campaign. A computer house in a campaign orders every class together whatever its credits, so the figure decides nothing there.
:::

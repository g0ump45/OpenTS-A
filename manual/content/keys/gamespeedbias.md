---
key: GameSpeedBias
summary: The multiplier folded into every house's build-time and ground-speed figures.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "1"
---

The value is combined into the figures a house is handed when it is assigned its difficulty. Build time is multiplied by one of them, alongside the country and difficulty [`BuildTime=`](/keys/buildtime/#scope-housetype) values; a ground unit's speed is multiplied by another. A figure above 1 therefore makes everything build more slowly and ground units move faster at the same time.

Unlike the country's contribution, this one is applied in campaign games too, as is the difficulty section's own build-time figure; only the country factor is dropped there.

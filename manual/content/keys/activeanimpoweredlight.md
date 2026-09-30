---
key: ActiveAnimPoweredLight
summary: Whether the first active slot's animation is destroyed and recreated with its house's power.
see_also: ["ActiveAnim", "ActiveAnimPowered", "system:power"]
when_omitted:
  kind: value
  value: "no"
---

The flag does not tint or light anything: it swaps the freeze for outright destruction and recreation. [Power](/systems/building-animations/#power) covers why it needs [`ActiveAnimPowered=no`](/keys/activeanimpowered/) beside it to have any effect at all.

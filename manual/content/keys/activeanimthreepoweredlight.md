---
key: ActiveAnimThreePoweredLight
summary: Whether the third active slot's animation is destroyed and recreated with its house's power.
see_also: ["ActiveAnimThree", "ActiveAnimThreePowered", "system:power"]
when_omitted:
  kind: value
  value: "no"
---

The flag does not tint or light anything: it swaps the freeze for outright destruction and recreation. [Power](/systems/building-animations/#power) covers why it needs [`ActiveAnimThreePowered=no`](/keys/activeanimthreepowered/) beside it to have any effect at all.

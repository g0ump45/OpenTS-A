---
key: VeteranCombat
summary: Weapon damage from an object holding the firepower ability is multiplied by this value plus one.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: "1"
---

The multiplier reaches only an object whose rank grants it the `FIREPOWER` ability through [`VeteranAbilities`](/keys/veteranabilities/) or [`EliteAbilities`](/keys/eliteabilities/); rank alone does not qualify. The default doubles damage, and `0` leaves it unchanged.

Scaling is applied last, after the house and per-object firepower biases. A sonic weapon and a weapon that fires through the fire particle system have their damage figure zeroed before this step, so they never gain anything from the ability.

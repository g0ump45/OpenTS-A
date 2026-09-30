---
key: VeteranArmor
summary: Damage taken by an object holding the armor ability is divided by this value plus one.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: "1"
---

This figure is a divisor, so raising it reduces damage taken: the default halves incoming damage, and `0` leaves it unchanged. It reaches only an object whose rank grants it the `STRONGER` ability through [`VeteranAbilities`](/keys/veteranabilities/) or [`EliteAbilities`](/keys/eliteabilities/).

The reduction is applied after the house and per-object armor biases and before the floor that keeps any damaging hit worth at least one point. Forced damage skips the whole chain, and so does a negative amount, which is how healing is delivered.

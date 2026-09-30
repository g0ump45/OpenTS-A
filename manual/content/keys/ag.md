---
key: AG
summary: Allows the projectile to be fired at targets that are on the ground.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "yes"
---

A weapon whose projectile is not anti-ground cannot fire on anything at ground level, which is how an anti-air weapon is kept from shooting at a landed aircraft. When a target scan arrives with no target category of its own, this setting contributes infantry, vehicles and buildings; [`AV=yes`](/keys/av/) on the same projectile cancels that contribution.

:::caution[`AG=no` on the first weapon slot rejects every ground candidate]
The target scan tests the first slot's projectile against the candidate's height whatever weapon would actually be fired, and rejects anything sitting at ground level rather than only a landed aircraft. An object whose first weapon is anti-air therefore picks no ground target automatically, even when its second weapon could hit one.
:::

The setting also gates the computer's wall targeting: a wall is worth nothing to an object whose first weapon's projectile is `AG=no`.

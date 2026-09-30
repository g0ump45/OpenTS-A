---
key: AA
summary: Allows the projectile to be fired at targets that are in the air.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "no"
---

A weapon whose projectile is not anti-aircraft cannot fire on anything that is airborne. The test is on the target being in the air, not on what it is, so an aircraft overhead, a [`JumpJet=yes`](/keys/jumpjet/) infantry in flight, and a vehicle lifted by a flying locomotor are all refused whatever else would allow the shot. The setting is also what lets an object shoot back at an aircraft that damaged it.

Separately, when a target scan arrives with no target category of its own, each weapon slot contributes the categories its projectile allows, and this setting contributes aircraft. [`AV=yes`](/keys/av/) on the same projectile cancels that contribution, because it answers with vehicles alone and stops. The firing restriction above is not affected by `AV`.

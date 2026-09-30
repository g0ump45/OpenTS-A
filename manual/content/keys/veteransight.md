---
key: VeteranSight
summary: Sight range of an object holding the sight ability is multiplied by this value plus one.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: "1"
---

The multiplier reaches only an object whose rank grants it the `SIGHT` ability through [`VeteranAbilities`](/keys/veteranabilities/) or [`EliteAbilities`](/keys/eliteabilities/). The default doubles the radius, and `0` leaves it unchanged.

Scaling is applied to the type's sight range after the height-based increase that lifts an object standing on high ground, and the widened radius is used the next time the object reveals terrain rather than at the moment it is promoted.

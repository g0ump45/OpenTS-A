---
key: DamageToFirestormDamageCoefficient
summary: How much firestorm charge a raised wall loses per point of damage aimed at one of its sections.
see_also: [FirestormWall, ChargeToDrainRatio, "system:laser-fences"]
when_omitted:
  kind: value
  value: "0.1"
---

A [`FirestormWall=yes`](/keys/firestormwall/) structure [takes no health damage at all while its house's wall is up](/systems/laser-fences/#damage-while-the-wall-is-up). Each incoming damage figure is multiplied by this value and taken off the countdown of the house's firestorm superweapon instead, never past zero, so a wall under fire runs down sooner rather than breaking open. At the stock coefficient ten points of damage cost one frame.

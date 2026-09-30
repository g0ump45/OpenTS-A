---
key: SpecialAnimThreeDamaged
summary: The animation the third special slot runs while the structure is damaged.
see_also: ["SpecialAnimThree", "SpecialAnim", "ConditionYellow"]
when_omitted:
  kind: inherited
  note: The animation SpecialAnimThree names.
---

[The damaged form](/systems/building-animations/#the-damaged-form) covers when a slot picks this name over [`SpecialAnimThree`](/keys/specialanimthree/). A depot asks for the healthy name at every point it [fills this slot](/keys/specialanim/#what-starts-a-special-animation), so this one is reached as the structure crosses the damage threshold with the animation already running, rather than at the moment the slot is filled.

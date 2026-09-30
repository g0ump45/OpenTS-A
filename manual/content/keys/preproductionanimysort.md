---
key: PreProductionAnimYSort
summary: The sorting bias applied to the pre-production animation, in leptons.
see_also: ["PreProductionAnim", "PreProductionAnimZAdjust"]
when_omitted:
  kind: value
  value: "0"
---

The bias that moves the pre-production animation within the drawing order of the objects sharing its layer. [Placement and draw order](/systems/building-animations/#placement-and-draw-order) covers how that differs from the depth bias, what the slot does to the AnimType's own sort bias, and the byte the figure has to fit in.

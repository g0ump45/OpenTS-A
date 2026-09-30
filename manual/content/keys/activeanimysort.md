---
key: ActiveAnimYSort
summary: The sorting bias applied to the first active slot's animation, in leptons.
see_also: ["ActiveAnim", "ActiveAnimZAdjust"]
when_omitted:
  kind: value
  value: "0"
---

The bias that moves the first slot's animation within the drawing order of the objects sharing its layer. [Placement and draw order](/systems/building-animations/#placement-and-draw-order) covers how that differs from the depth bias, what the slot does to the AnimType's own sort bias, and the byte the figure has to fit in.

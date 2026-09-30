---
key: AALimit
summary: Parsed ceiling on anti-aircraft buildings that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", AARatio, BuildAA]
when_omitted:
  kind: value
  value: "10"
---

Anti-aircraft cover is not planned as a category of its own with a count to stay under. [The defense planner](/systems/ai-base-building/#base-defenses) fills each placeholder with whichever of the three categories the chosen quadrant is thinnest in, so how many anti-aircraft buildings a computer base ends up with follows from the coverage already stamped around it.

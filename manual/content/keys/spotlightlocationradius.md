---
key: SpotlightLocationRadius
summary: Distance ahead of a structure, in leptons, that its spotlight beam is aimed at.
see_also: [SpotlightMovementRadius, SpotlightRadius, HasSpotlight]
when_omitted:
  kind: value
  value: "1000"
---

A spotlight is aimed this far in front of the structure carrying it, along the direction that structure faces, and the beam rests there before it begins to move. The stored figure is a little under four cells.

It is also the inner edge of the grading that widens the beam as it travels: while the beam is nearer its structure than this, it counts as being at rest, and only past this distance does it start picking up the sweep stages that enlarge its detection radius. A beam [set to follow a target](/mapping/actions/taction-change-spotlight-behavior/) also widens the pool of light it casts once it passes this distance, by the sweep stage it has reached plus 80 and never past 89.

:::danger[Closing the gap to `SpotlightMovementRadius` divides by zero]
The sweep grading divides the distance traveled by a tenth of the span between this key and [`SpotlightMovementRadius`](/keys/spotlightmovementradius/). That tenth is computed in whole leptons, so any pair of values less than 10 leptons apart makes it zero, and the division that follows runs on every beam that has left its resting point.
:::

---
key: SpotlightMovementRadius
summary: Distance behind a structure at which its spotlight's sweep pivots, and the range beyond which a followed target is dropped.
see_also: [SpotlightLocationRadius, SpotlightRadius, HasSpotlight]
when_omitted:
  kind: value
  value: "2000"
---

The point a sweeping beam turns about sits this far behind its structure, along the direction the structure faces and opposite the aim point placed by [`SpotlightLocationRadius`](/keys/spotlightlocationradius/). The beam therefore swings on an arc whose radius is the two figures added together, which at the stored pair is a little under twelve cells.

The span between the two radii is graded in tenths, and every tenth the beam has traveled out from its structure widens what it can see. [`SpotlightRadius`](/keys/spotlightradius/) covers that widening.

A beam [set to follow a target](/mapping/actions/taction-change-spotlight-behavior/) holds onto it only while the target is nearer to the structure than this figure.

:::danger[A dropped target leaves the beam nowhere]
A following beam reverts to sweeping the moment it has no target — because none was found when the behavior was taken up, or because the one it had was destroyed or passed this distance — and on that frame its position is written from an indeterminate value instead of from where it stood. Because the beam now counts as sweeping, the intruder scan runs on that same frame, testing the map cells around wherever that coordinate has landed.
:::

---
key: AttackingAircraftSightRange
summary: Radius in cells revealed when a player-controlled aircraft fires from or at shrouded ground.
see_also: ["system:map-visibility", Sight]
when_omitted:
  kind: value
  value: "5"
---

The reveal is taken at the aircraft's own position, in place of its [`Sight=`](/keys/sight/), whenever it fires and its house is under the local player's control. The condition is met by any one of the aircraft's own coordinate, three coordinates two cells out from it on the diagonals, and the target's center lying under shroud.

The radius is a plain count of cells and is not converted from a lepton distance.

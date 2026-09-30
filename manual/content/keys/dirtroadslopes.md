---
key: DirtRoadSlopes
summary: The tile set that supplies the eight pieces carrying a dirt road up a ramp.
see_also: [DirtRoadCurve, DirtRoadJunction, PavedRoadSlopes]
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is bound to the role.
no_effect: true
---

The eight pieces close the [random map generator](/formats/map-seed/)'s road library, appended after the 101 flat pieces counted from [`DirtRoadCurve`](/keys/dirtroadcurve/), and each carries the same connection data the flat pieces do. Nothing ever selects one: the generator draws its candidates from a fixed list of library entries that stops short of the ramps, so a road it lays stops at a slope rather than climbing it. [`PavedRoadSlopes`](/keys/pavedroadslopes/) is the paved counterpart, and it is equally inert.

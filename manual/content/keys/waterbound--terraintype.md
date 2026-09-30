---
key: WaterBound
scope: terraintype
label: Water-based terrain object
see_also: [Foundation]
when_omitted:
  kind: value
  value: "no"
---

Placing a terrain object tests every cell of its footprint, and the setting picks which movement kind that test is taken for. A water-based object needs a land type the floating movement kind can cross; every other object needs one a tracked vehicle can cross. A cell whose land type carries a cost of zero for the kind being tested refuses the object, and so does a cell outside the local radar bounds or holding any overlay.

Neither branch consults [`Buildable=`](/keys/buildable/): a terrain object is placed against movement costs, not against the flag that admits foundations. The object is simply not placed when any cell of its footprint refuses it.

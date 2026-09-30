---
key: DirtRoadJunction
summary: The tile set that supplies the eleven dirt road junctions.
see_also: [DirtRoadCurve, DirtRoadStraight, DirtRoadSlopes]
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is bound to the role.
---

A rural road network opens on a junction, and this role is where the [random map generator](/formats/map-seed/) finds one. All eleven shapes counted from it are tried once at the starting cell, beginning at a randomly chosen shape so that networks do not all open the same way, and the network is abandoned outright when none of the eleven fits.

The eleven also fall inside the run of 101 tiles that [`DirtRoadCurve`](/keys/dirtroadcurve/) fixes, since that run's length is the curve, junction and straight counts added together. The two roles therefore describe overlapping ground and agree only while their sets follow one another.

---
key: Crater
scope: animtype
label: Animation crater
see_also: ["Scorch", "Flamer", "Craters", "CraterLevel"]
when_omitted:
  kind: value
  value: "no"
---

A crater is stamped where the animation stands, on the frame whose artwork covers the most ground, and only while the animation is standing less than 30 leptons above the ground beneath it. The crater is picked at random from the smudge types that declare themselves craters and fit the location: a cell that already carries a smudge of any kind takes none, and neither does a ramp, a cell holding an overlay, a cell a building stands on, a cell outside the playable area, or ground the theater's tile does not allow marks on. Multiple cell craters join the candidates only where that largest frame measures more than 48 pixels across and 40 down.

Cratering also strips Tiberium from the cell, as [Damage](/systems/tiberium/#damage) explains. Both effects run each time the animation passes that frame, so a looping animation repeats them, though a cell already marked takes no second mark.

[`Scorch`](/keys/scorch/) takes precedence over this setting: an animation declaring both leaves a scorch mark half the time and a crater the other half, never both.

:::caution[A thrown animation rarely craters]
The frame test is skipped for as long as an animation is bouncing, so a [`Bouncer=yes`](/keys/bouncer/) or [`IsMeteor=yes`](/keys/ismeteor/#scope-animtype) animation marks the ground only when its largest frame happens to be its first, and then it marks the point it was thrown from rather than the point it comes down on. The terrain a meteor impact slumps is a separate effect that [`CraterLevel`](/keys/craterlevel/) covers.
:::

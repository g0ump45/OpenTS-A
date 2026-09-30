---
key: TargetLaserThick
summary: Draws the sighting laser two rows high.
see_also: ["system:action-lines", TargetLaser, TargetLaserDashed, TargetLaserDropShadow]
when_omitted:
  kind: value
  value: "no"
---

A second copy of the line is drawn one row below the first, and the squares on its ends grow from two pixels to four. The sighting laser is the line a firing vehicle with [`TargetLaser=yes`](/keys/targetlaser/) draws to where its shot is aimed; [Action lines](/systems/action-lines/) covers when it is drawn.

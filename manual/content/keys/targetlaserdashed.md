---
key: TargetLaserDashed
summary: Draws the sighting laser as dashes rather than a solid line.
see_also: ["system:action-lines", TargetLaser, TargetLaserColor, TargetLaserThick]
when_omitted:
  kind: value
  value: "yes"
---

The sighting laser is the line a firing vehicle with [`TargetLaser=yes`](/keys/targetlaser/) draws to where its shot is aimed. Its dashes are one pixel on and one off and step seven pixels along the line each game frame. [Action lines](/systems/action-lines/) covers when it is drawn.

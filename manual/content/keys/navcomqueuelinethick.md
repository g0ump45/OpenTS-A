---
key: NavComQueueLineThick
summary: Draws the queued-destination lines two rows high.
see_also: ["system:action-lines", ShowNavComQueueLines, NavComQueueLineDashed, NavComQueueLineDropShadow]
when_omitted:
  kind: value
  value: "no"
---

A second copy of each line is drawn one row below the first, and the squares on the lines' ends grow from three pixels to four. The lines run through a selected object's queued destinations beyond its movement line; [Action lines](/systems/action-lines/) covers when they are drawn.

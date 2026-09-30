---
key: AlwaysShowActionLines
summary: Keeps a selected object's order lines drawn instead of fading them out after an order.
see_also: ["system:action-lines", UnitActionLines, ShowNavComQueueLines]
when_omitted:
  kind: value
  value: "no"
---

With `yes` the lines stay drawn for as long as the object is selected. With `no` they show for 25 frames after a selection or an order, and while the queue-move key is held. [`UnitActionLines`](/keys/unitactionlines/) in `sun.ini` still switches them off altogether, and [Action lines](/systems/action-lines/) covers what is drawn.

```ini title="UI.INI"
[Ingame]
AlwaysShowActionLines=yes
```

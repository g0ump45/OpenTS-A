---
key: ShroudRate
summary: Game minutes between shroud regrowth passes.
see_also: ["system:map-visibility", ShroudGrow]
when_omitted:
  kind: value
  value: "4"
---

The value is converted to frames at 900 frames to the game minute, and the timer is reloaded with that figure after each pass. `ShroudRate=0` stops the regrowth entirely, exactly as [`ShroudGrow=no`](/keys/shroudgrow/) does.

The timer starts a scenario at zero, so the first eligible frame runs a pass immediately; the interval spaces only the passes after that one. Each pass costs the player one cell around the edge of the revealed area, so the value sets how fast the shroud closes in rather than how much it takes.

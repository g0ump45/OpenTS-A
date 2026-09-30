---
key: StartWalkFrame
summary: The frame a shape-drawn vehicle's walking animation begins at.
see_also: ["WalkFrames", "StartStandFrame", "Facings"]
when_omitted:
  kind: value
  value: "0"
---

The walk block runs from here: one run of [`WalkFrames`](/keys/walkframes/) frames for each facing in turn, in the [`Facings`](/keys/facings/) block order. A vehicle that declares no [`StandingFrames`](/keys/standingframes/) is drawn from this same block while it stands still, on the first frame of its facing's run.

```ini title="art.ini"
[REAPER] ; the Image ID of the stock Cyborg Reaper
Facings=8
StandingFrames=1
StartStandFrame=0 ; one standing frame per facing, frames 0-7
WalkFrames=12
StartWalkFrame=8  ; eight runs of 12, frames 8-103
```

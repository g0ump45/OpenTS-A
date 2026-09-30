---
key: StartStandFrame
summary: The frame a shape-drawn vehicle's standing artwork begins at.
see_also: ["StandingFrames", "WalkFrames", "Facings", "StartWalkFrame"]
when_omitted:
  kind: computed
  note: Facings × WalkFrames, counted from frame 0 rather than from StartWalkFrame; 0 for a vehicle with no standing frames, which is drawn from its walk block instead.
---

The standing block runs from here: one run of [`StandingFrames`](/keys/standingframes/) frames for each facing in turn. The derived default is worked out from the [`Facings`](/keys/facings/) and [`WalkFrames`](/keys/walkframes/) figures of the same section, so changing either moves this frame number with it.

Writing the value out is how artwork that does not follow the walk-then-stand order is described. The stock Core Defender and Cyborg Reaper both put their standing frames first and their walk frames after them:

```ini title="art.ini"
[DEFENDER] ; the Image ID of the stock Core Defender
Facings=8
WalkFrames=8
StartStandFrame=0 ; frames 0-7
StartWalkFrame=8  ; frames 8-71
```

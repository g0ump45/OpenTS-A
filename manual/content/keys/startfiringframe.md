---
key: StartFiringFrame
summary: The frame a shape-drawn vehicle's firing animation begins at.
see_also: ["FiringFrames", "StandingFrames", "WalkFrames", "Facings"]
when_omitted:
  kind: computed
  note: Facings × (StandingFrames + WalkFrames), counted from frame 0; a vehicle with no firing frames takes the derived StartStandFrame, settled before the section's own value for that key is read.
---

The firing block runs from here: one run of [`FiringFrames`](/keys/firingframes/) frames for each facing in turn. The derived default assumes the file is laid out walk block, standing block, firing block, and it is worked out from the [`Facings`](/keys/facings/), [`WalkFrames`](/keys/walkframes/) and [`StandingFrames`](/keys/standingframes/) figures of the same section.

Writing the value out is how a different layout is described. The stock Core Defender puts its standing block first and its walk block after it, then names the frame its firing block begins at:

```ini title="art.ini"
[DEFENDER] ; the Image ID of the stock Core Defender
Facings=8
WalkFrames=8
FiringFrames=12
StartStandFrame=0
StartWalkFrame=8
StartFiringFrame=72 ; eight runs of 12, frames 72-167
```

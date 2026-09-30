---
key: IntentionalDriftVelocity
summary: The speed a levitating unit moves at while it is drifting rather than thrusting.
see_also: ["ProximityDistance", "MaxBlockCount", "Acceleration", "InitialBoost"]
when_omitted:
  kind: value
  value: "0.3"
---

A drift sets the unit's speed to this figure outright, clears any thrust in progress, and switches the per-frame loss off entirely, so the unit holds the speed until something takes it out of the drift. Three things start one: closing to within [`ProximityDistance`](/keys/proximitydistance/) of the target or destination being steered at, drifting back to the middle of its own cell after a blocked move, and leaving that cell again once re-centered. A drift aimed at a point is also clipped per axis so it cannot overshoot that point in one frame.

The figure is in leptons per frame — 256 leptons to a cell, 15 frames to the second — so a value of `12` carries the unit about two thirds of a cell each second and one of `0.3` about a cell a minute.

:::danger[A drift of more than a cell per frame can hang the game]
The step that decides whether a levitating unit may enter the cell it is moving into first works out which of the eight neighbors that cell is, and the search never gives up: a destination more than one cell away leaves it spinning, and the game stops responding. A movement whose horizontal or vertical component exceeds 256 leptons in one frame can land two cells away and reach that state; the figure is a speed split between the two axes, so the direction of travel decides whether it does. This figure and the speeds a thrust builds must therefore stay well below 256. Nothing in the section clamps them.
:::

[`Drag`](/keys/drag/) covers which objects read this section and the `[General]` section a file must carry for any of it to be read at all.

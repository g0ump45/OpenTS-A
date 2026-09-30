---
key: InitialBoost
summary: The speed a levitating unit gains at once when a thrust begins.
see_also: ["Acceleration", "AccelerationDuration", "Drag", "IntentionalDriftVelocity"]
when_omitted:
  kind: value
  value: "1.5"
---

The figure is added to the unit's velocity on the frame a thrust starts, in the direction the thrust is aimed, before any of the per-frame [`Acceleration`](/keys/acceleration/#scope-levitation-controls) is applied. It is in leptons per frame — 256 leptons to a cell, 15 frames to the second — and it is added to whatever the unit was already carrying rather than replacing it, so a thrust taken while the unit is already moving compounds with the motion it had.

It is applied on every thrust, whether the unit is wandering at random or heading for something, and it is the whole of a thrust's effect when [`AccelerationDuration`](/keys/accelerationduration/) is zero. Nothing caps the result; [`IntentionalDriftVelocity`](/keys/intentionaldriftvelocity/) describes what happens once one frame's movement crosses more than a single cell.

[`Drag`](/keys/drag/) covers which objects read this section and the `[General]` section a file must carry for any of it to be read at all.

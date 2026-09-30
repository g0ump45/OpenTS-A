---
key: Acceleration
scope: levitation-controls
label: Levitation thrust
see_also: ["AccelerationDuration", "InitialBoost", "Drag", "AccelerationProbability"]
when_omitted:
  kind: value
  value: "0.5"
---

The figure is added to a levitating unit's velocity on each frame of a thrust, in the direction the thrust was aimed, for [`AccelerationDuration`](/keys/accelerationduration/) frames. It is in leptons per frame gained per frame — 256 leptons to a cell, 15 frames to the second. [`Drag`](/keys/drag/) is subtracted over the same frames, so the speed a thrust reaches is roughly the two figures' difference multiplied by the duration, on top of the [`InitialBoost`](/keys/initialboost/) the thrust opens with.

Nothing caps the result. [`MaxVelocityWhenFollowing`](/keys/maxvelocitywhenfollowing/) and [`MaxVelocityWhenPissedOff`](/keys/maxvelocitywhenpissedoff/) decide when a coast ends, and [`MaxVelocityWhenHappy`](/keys/maxvelocitywhenhappy/) decides when a fresh thrust may begin — none of them decides how fast a thrust may leave the unit traveling, so a large figure here raises the unit's top speed without limit; [`IntentionalDriftVelocity`](/keys/intentionaldriftvelocity/) describes what happens once one frame's movement crosses more than a single cell.

[`Drag`](/keys/drag/) covers which objects read this section and the `[General]` section a file must carry for any of it to be read at all.

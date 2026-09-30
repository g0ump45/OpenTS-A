---
key: FiringSyncFrame2
summary: The countdown value at which the second round of a burst leaves a shape-drawn vehicle.
see_also: ["FiringSyncFrame1", "FiringFrames", "Burst"]
when_omitted:
  kind: value
  value: "-1"
---

This is the same gate as [`FiringSyncFrame1`](/keys/firingsyncframe1/), applied to the second round of a [`Burst`](/keys/burst/) instead of the first. That page covers the countdown the value is matched against, what an unmatched figure costs, and the reach of both settings. Rounds after the second cannot be tied to the animation at all.

A weapon that fires one round at a time never reaches this setting, since the round it gates is the second of a burst.

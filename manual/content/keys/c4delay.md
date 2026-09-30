---
key: C4Delay
summary: The delay in minutes between arming a demolition charge and its detonation.
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: ".03"
---

The value is multiplied by 900 frames where it is used, giving 27 frames — about 1.8 seconds at 15 frames a second — at the engine default. Half that figure becomes the number of frames the structure spends flashing as a designated target, so a longer delay also makes the warning last longer.

Nothing shortens or cancels the countdown once it is running. [Detonation](/systems/capture/#detonation) covers the damage that ends it.

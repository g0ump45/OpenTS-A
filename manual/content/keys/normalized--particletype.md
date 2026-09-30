---
key: Normalized
scope: particletype
label: Particle state pacing
see_also: ["StateAIAdvance", "FinalDamageState"]
when_omitted:
  kind: value
  value: "no"
---

The particle's own [`StateAIAdvance`](/keys/stateaiadvance/) is discarded and recomputed as the particle is created. The engine works out how long the particle needs to reach its target at its current speed, divides that by one more than [`FinalDamageState`](/keys/finaldamagestate/), adds one to the result and truncates it to a whole number of frames between state advances — so the particle finishes its damage-state sequence just as it arrives, however far it has to travel.

:::caution[A particle with no horizontal course gets a fixed fallback]
The flight time is derived from the particle's horizontal velocity. When its origin and its target sit at the same horizontal position, that velocity is zero on both axes and the calculation falls back to a fixed 9999 frames before dividing, leaving an interval far longer than any authored one.
:::

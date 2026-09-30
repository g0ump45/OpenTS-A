---
key: SpotlightSpeed
summary: Turn rate a spotlight beam builds toward, in radians per frame.
see_also: [SpotlightAcceleration, SpotlightAngle, HasSpotlight]
when_omitted:
  kind: value
  value: ".05"
---

A sweeping beam adds [`SpotlightAcceleration`](/keys/spotlightacceleration/) to its turn rate every frame for as long as the rate is still below this figure, in whichever direction it is traveling. Because that test is made before the step, the rate settles at the first value to reach or pass this figure — up to one acceleration step beyond it, which at the stored pair leaves it at `.055`.

A beam [set to circle its structure](/mapping/actions/taction-change-spotlight-behavior/) reads the figure differently: it consults neither the acceleration nor [`SpotlightAngle`](/keys/spotlightangle/), and simply advances four times this figure in radians every frame, wrapping at a full turn. The stored figure brings such a beam round in about thirty-one frames.

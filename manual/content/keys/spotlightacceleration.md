---
key: SpotlightAcceleration
summary: Radians per frame by which a sweeping spotlight's turn rate rises and falls.
see_also: [SpotlightSpeed, SpotlightAngle, HasSpotlight]
when_omitted:
  kind: value
  value: ".005"
---

Inside its arc a sweeping beam gains this much turn rate every frame for as long as the rate is below [`SpotlightSpeed`](/keys/spotlightspeed/). Once the beam has crossed half of [`SpotlightAngle`](/keys/spotlightangle/) the same figure is taken off the rate each frame instead, and the beam reverses on the frame the rate reaches zero. It therefore sets both how briskly a sweep gets going and how far past the edge of the nominal arc the beam coasts before it turns back: a smaller figure gives a gentler start and a longer overshoot.

A beam set to circle its structure or follow a target does not consult it.

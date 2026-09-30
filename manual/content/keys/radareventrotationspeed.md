---
key: RadarEventRotationSpeed
summary: Radians a radar event's box turns each frame.
see_also: ["system:map-visibility", RadarEventSpeed, RadarEventMinRadius]
when_omitted:
  kind: value
  value: ".1"
---

Every [radar event](/reference/enums/radar-event/) starts with this turn step and spins its box by the current step each frame. While the box is still closing in the step is held at the configured value: at the default of a tenth of a radian that is a little under six degrees a frame, a full turn in about sixty-three frames. Once the radius has reached [`RadarEventMinRadius`](/keys/radareventminradius/), each further frame that fails to settle the box turns it and then cuts the step by two percent of the configured value, never below a third of it, so a box that has to come round again turns more slowly each lap.

The box stops turning on the first frame at that radius when it stands less than one step past the orientation it opened in; it turns by that same fraction once more and comes to rest. That frame is also when [`RadarEventDurations`](/keys/radareventdurations/) and [`RadarEventVisibilityDurations`](/keys/radareventvisibilitydurations/) are loaded, and only an event that has stopped turning is ever removed.

:::caution[A non-positive step never settles]
At zero the box never turns, so the residual angle the settle test measures stays a hair above zero and the test can never pass. Its timers are never loaded and the event is never removed: it goes on being drawn for the rest of the match, and for the three suppressible kinds goes on swallowing later events of its kind. A negative step still settles, because it drives that residual angle negative and the test passes as soon as the residual falls below the step.
:::

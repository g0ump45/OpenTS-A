---
key: IsLimpetDrone
summary: Runs a vehicle's shape through a ten-frame loop and draws it without facings.
see_also: ["Jellyfish", "Image", "DeploysInto"]
when_omitted:
  kind: value
  value: "no"
---

The flag is presentational. A vehicle carrying it starts on frame 0 with its stage counter advancing once per game frame, and is sent back to frame 0 the moment the counter reaches 10, so its artwork loops over frames 0 through 9 in about two thirds of a second. It is then drawn straight from that frame with no facing frames at all, so the shape never turns with the vehicle's heading.

Nothing else in the engine reads it. Everything else a drone does follows from the rest of its section — what it turns into through [`DeploysInto`](/keys/deploysinto/), how it moves, what it may be targeted by — and clearing the flag changes none of that, only the animation.

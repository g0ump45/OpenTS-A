---
enum_id: LightBehaviorType
slug: spotlight-behavior
title: Spotlight behavior
summary: Modes a structure's spotlight beam runs in, from sweeping an arc to standing still and undrawn.
representation: integer
bindings:
  key_value_types: []
  scripting_parameter_types: [spotlight-behavior]
source_files: [code/blight.hh, code/blight.cpp, code/building.cpp]
values:
  - { constant: LIGHT_BEHAVIOR_NONE, value: 0, input: "0", meaning: "Beam held in place and not drawn at all." }
  - { constant: LIGHT_BEHAVIOR_SWEEP, value: 1, input: "1", meaning: "Sweep the beam back and forth across an arc centered on the structure's facing." }
  - { constant: LIGHT_BEHAVIOR_CIRCLE, value: 2, input: "2", meaning: "Carry the beam around the structure at a constant rate." }
  - { constant: LIGHT_BEHAVIOR_FOLLOW, value: 3, input: "3", meaning: "Track the nearest enemy soldier or vehicle standing where the beam sat when the mode was set." }
---

`Follow` drops back to `Sweep` the moment its quarry dies or moves beyond [`SpotlightMovementRadius`](/keys/spotlightmovementradius/), which makes it a temporary state rather than a standing one; a beam is given `Sweep` when its structure is placed, so `0` is only ever reached by a map or a trigger asking for it. Which of the modes runs the intruder scan, and when, is covered by [`SpotlightRadius`](/keys/spotlightradius/).

:::caution[A value outside the four is drawn but never moves]
The four modes are the whole of this domain and no branch of the beam logic answers to anything else. A beam holding a figure above `3`, or a negative one, is still visible, since only `0` suppresses the drawing, but nothing moves it and nothing scans from it, so it sits over one spot until [something sets its behavior again](/mapping/actions/taction-change-spotlight-behavior/).
:::

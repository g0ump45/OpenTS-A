---
key: Sticky
summary: Parsed flag that the engine never uses.
no_effect: true
see_also: ["Damage"]
when_omitted:
  kind: value
  value: "no"
---

The name promises that the animation pins itself to whatever unit is standing where it appears, which is how an impact explosion would ride the vehicle it went off on. Nothing reads the flag.

Whether an animation ends up pinned to an object is settled by the code that creates it — a parachute pinned to what it is lowering, the fire an object catches when it takes damage, the sparks an EM pulse leaves on what it disabled — and never by the animation's own type.

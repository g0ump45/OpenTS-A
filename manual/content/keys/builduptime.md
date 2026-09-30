---
key: BuildupTime
summary: The length of a structure's construction animation, in game minutes.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: ".05"
---

The value in frames is divided by the animation's step count when the buildup art is loaded, truncating once at the end, which gives the delay between one buildup frame and the next; at the default that is three seconds spread across however many steps the type has. The step count is half the number of frames in the buildup art, or [`GateStages`](/keys/gatestages/) plus one for a [`Gate=yes`](/keys/gate/) type.

One value covers every structure in the game, so a type with more buildup frames spends less time on each of them rather than taking longer overall. [Buildup](/systems/production/#buildup) covers the game-speed adjustment applied to the resulting rate and the construction-yard handshake that runs alongside it.

A [`Theater=yes`](/keys/theater/) structure has its construction animation timed again as the theater is set up, from every frame in the file at a fixed five seconds, so this value does not reach it.

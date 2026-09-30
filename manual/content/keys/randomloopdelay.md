---
key: RandomLoopDelay
summary: The bounds, in game frames, of the pause inserted between one pass of a looping animation and the next.
see_also: ["LoopCount", "RandomRate", "Rate", "Report"]
when_omitted:
  kind: value
  value: "0,0"
---

A pause is drawn from between the two bounds each time a pass ends and another begins, so the pair needs [`LoopCount`](/keys/loopcount/) above one to do anything. While both bounds are zero the animation loops with no pause at all. Fifteen frames make a second of game time, so `RandomLoopDelay=10,300` is a pause of between two thirds of a second and twenty seconds.

The animation is not drawn while it is paused and does not advance. When the pause runs out the animation's opening side effects are run a second time: its [`Report=`](/keys/report/#scope-animtype) sound plays again, a [`TiberiumChainReaction=yes`](/keys/tiberiumchainreaction/) animation sets off the tiberium beneath it again, and an animation whose largest frame is its first lays its scorch mark or crater down again. A looping animation with a sound and a pause therefore repeats that sound once per pass, which is what makes the pause worth having on an idle effect and unusable on a noisy one.

A value carrying only one number leaves the upper bound undefined rather than defaulting it, so the pause length is taken from whatever happened to be in memory. Both halves have to be written.

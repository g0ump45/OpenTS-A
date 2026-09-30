---
key: PingPong
summary: Reverses the animation's direction each time it reaches either end of its frames.
see_also: ["LoopCount", "LoopEnd", "End", "Reverse", "Start"]
when_omitted:
  kind: value
  value: "no"
---

On reaching either end of its range the animation flips its step and walks back the way it came, instead of snapping to the start or finishing. Which pair of frames it turns on depends on [`LoopCount`](/keys/loopcount/): an animation left on a single pass turns at the stage count in [`End`](/keys/end/) and at its first stage, while one given more than one pass turns at [`LoopEnd`](/keys/loopend/) and at the stage matching [`Start`](/keys/start/).

The stage that triggered a turn is held for one frame before the animation steps back, so the frame at the top of the range is displayed. With the range left at the shape's own frame count that frame is one past the last frame in the shape and draws nothing, which shows as a blink at every turn. Setting the range one frame shorter removes it.

:::caution[A ping-pong animation does not finish on its own]
The turn is taken in place of the end-of-pass bookkeeping, and it is tested first on a condition that already covers the end-of-pass test, so that bookkeeping is not reached: the animation spends no passes, never chains through [`Next=`](/keys/next/), and never removes itself. It plays until something else takes it away — the structure whose slot it fills stopping it, the object it is pinned to being destroyed, or the scenario ending. An animation created for its own sake with this flag set stays in the game for the rest of the mission. The one way out is [`Reverse=yes`](/keys/reverse/) on an animation left on a single pass with a non-zero [`Start`](/keys/start/): the reverse end test is the one condition the turn does not cover, and it fires as the animation steps down past that figure.
:::

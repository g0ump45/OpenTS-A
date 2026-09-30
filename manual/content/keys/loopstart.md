---
key: LoopStart
summary: The frame a looping animation returns to at the start of each new pass.
see_also: ["LoopEnd", "LoopCount", "Start", "Reverse"]
when_omitted:
  kind: value
  value: "0"
---

The value is a frame number in the shape, not a count from [`Start`](/keys/start/). It is consulted only when a pass has just ended and the animation still has passes left, so it needs [`LoopCount`](/keys/loopcount/) above one to do anything; the opening pass always begins on the animation's start frame whatever this says.

A [`Reverse=yes`](/keys/reverse/) animation ignores it entirely — a reversed pass restarts on [`LoopEnd`](/keys/loopend/) and walks back down.

A frame number below the animation's start frame is turned back into itself: the engine subtracts the start frame to get a stage and adds it again to draw, so the pass restarts on exactly that frame. A figure past the end of the shape is not corrected, and one far enough above the start frame restarts the animation past the end of its own stage count, so the pass ends again on the next advance and the animation burns through its remaining passes at one per frame delay.

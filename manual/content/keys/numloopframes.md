---
key: NumLoopFrames
summary: Parsed frame count that the engine never uses.
no_effect: true
see_also: ["StartFrame", "EndStateAI", "StateAIAdvance"]
when_omitted:
  kind: value
  value: "1"
---

The name promises a loop length, but how long a particle's sequence runs is set by [`EndStateAI`](/keys/endstateai/) and [`StateAIAdvance`](/keys/stateaiadvance/), and whether it repeats by [`DeleteOnStateLimit`](/keys/deleteonstatelimit/). No drawing or state path reads the figure stored here.

---
key: LoopCount
summary: The number of passes an animation of the type makes before it ends or chains.
see_also: ["LoopStart", "LoopEnd", "End", "PingPong", "Next", "RandomLoopDelay"]
when_omitted:
  kind: value
  value: "0"
---

The figure is multiplied by the number of passes the code creating the animation asks for — one, for almost everything that creates an animation — and the product is what the animation counts down. `0` and `1` both give a single pass, because a product below one is raised to one.

More than one pass changes which frames play. The opening pass begins on [`Start`](/keys/start/) and ends on [`LoopEnd`](/keys/loopend/); each pass after it begins on [`LoopStart`](/keys/loopstart/) and ends on `LoopEnd`; and the final pass begins on `LoopStart` but runs to the end of the stage count in [`End`](/keys/end/) instead.

The count is kept in a single byte, which decides what the extremes do:

- `-1` is stored as 255, and 255 is the one value that is never counted down — the animation loops until something else takes it away. This is how an animation that has to run for as long as the structure or effect it belongs to is written.
- A figure of 256 or more wraps into the byte before the raise to one is applied, so `LoopCount=256` gives a single pass and `LoopCount=257` gives one as well.
- A negative figure other than `-1` wraps to a large positive count: `LoopCount=-2` runs 254 passes.

```ini title="art.ini"
[MYREFN_C] ; an active animation for a refinery
Image=MYREFN_C
LoopStart=0
LoopEnd=16
LoopCount=-1  ; runs until the structure stops it
Rate=350
Surface=yes
```

A [`PingPong=yes`](/keys/pingpong/) animation normally spends no pass at all, so the count only chooses which pair of frames it turns around on.

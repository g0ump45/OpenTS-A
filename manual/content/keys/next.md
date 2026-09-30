---
key: Next
summary: The animation this one turns into instead of finishing.
see_also: ["LoopCount", "Start", "Surface", "Rate", "End"]
when_omitted:
  kind: value
  value: "none"
---

When the last pass finishes, the animation does not end: it adopts the named type in place and plays on. Nothing new is created and nothing is removed, so an explosion that settles into a column of smoke is one object from start to finish rather than two.

The named type's stage count, loop count, frame delay and rate range all take over at that moment, and its [`Report=`](/keys/report/#scope-animtype) sound is played as though the animation had just begun. The chain is followed one type at a time, each time the animation reaches an end, so a pair of types naming each other keeps one animation alive indefinitely rather than building anything up.

A name no `[Animations]` entry declares does not fail the read — an empty animation type is created under that name instead. An animation that chains into one of those holds no artwork and no stages, so it disappears on its next logic frame.

## What the change of type does not carry over

- The animation is put on its new type's [`Start`](/keys/start/) as a stage, and the frame drawn is that figure added to the stage, so a chained-to type whose start frame is not zero opens on twice that frame.
- The layer and the height are those the animation was created with, so the new type's [`Surface=`](/keys/surface/) is not consulted and the animation stays where the first type put it.
- [`Reverse=yes`](/keys/reverse/) on the new type is not applied; the animation keeps stepping the way it already was.
- Demand-loaded artwork is given back for the type the animation was holding when it was removed, so the earlier links in a chain keep theirs for the rest of the scenario however they are flagged.

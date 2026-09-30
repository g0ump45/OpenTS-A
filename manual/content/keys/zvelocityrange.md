---
key: ZVelocityRange
summary: The spread of upward speeds a spark is thrown at.
see_also: ["MinZVelocity", "XVelocity", "YVelocity", "BehavesLike"]
when_omitted:
  kind: value
  value: "1"
---

How far above [`MinZVelocity`](/keys/minzvelocity/) a [`Spark`](/keys/behaveslike/#scope-particletype) particle's initial upward speed may reach, in leptons a frame. Each spark draws a random amount below this figure and adds it to that floor, so the range alone decides how ragged the top of a shower looks while the floor decides how high it goes.

The one random direction a whole burst shares draws its vertical part from this figure on its own, without the floor, and that draw may be negative — so a burst thrown in a random direction can be tipped downward even though no individual spark ever is.

:::danger[Zero stops the game]
The random amount is drawn by dividing by this figure, so `ZVelocityRange=0` divides by zero and the game stops the moment a spark system holding the type fires its first burst.
:::

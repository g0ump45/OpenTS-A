---
key: BlockagePathDelay
summary: Frames a ground object spends preferring to wait out a moving obstruction before it insists on routing around one.
see_also: [PathDelay]
when_omitted:
  kind: value
  value: "60"
---

The value is a raw frame count, so the default is four seconds at 15 frames to the second. It is loaded into the object's own countdown twice: once when the object is given a destination, and again the first time a step is refused because another moving object stands in the way.

While that countdown is running, a retry searches with moving obstacles merely preferred against, which usually produces the same route again and leaves the object waiting for the other one to clear. Once it reaches zero the retry prices a cell held by a moving object at a thousand times a clear step instead of four, so the search takes almost any detour over waiting — but it still routes through the blocker when no detour exists. Raising the figure makes traffic queue up behind itself for longer; lowering it sends objects around each other sooner and spreads them over more ground.

The driving, walking, mechanical and hovering locomotors all use the same countdown, and reaching zero only changes what a retry asks for — the object is not rerouted until it is blocked again.

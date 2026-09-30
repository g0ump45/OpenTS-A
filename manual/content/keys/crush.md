---
key: Crush
summary: How close a crushable target must be before a crusher drives over it instead of shooting.
see_also: ["Crusher", "Crushable", "PlayerAutoCrush", "AutoCrush", "system:difficulty"]
when_omitted:
  kind: value
  value: "1.5"
---

The distance is written in cells and measured between the two objects. Two decisions read it, and both are reached only for a house under computer control.

The first is the approach step. A unit carrying [`Crusher=yes`](/keys/crusher/), or one that has earned the crush ability, whose target is a [`Crushable=yes`](/keys/crushable/#scope-aircrafttype) object standing inside this distance, is sent to drive onto the target instead of closing to weapon range.

The second is retaliation. A unit that takes a hit from an enemy it could crush drives at the attacker rather than firing back, provided that attacker stands within this distance and the house's IQ has reached [`[IQ] AutoCrush`](/keys/autocrush/#scope-global-rules). A house in difficulty slot 2, the `[Difficult]` section, never does it — for a computer house that is the slot the Easy setting hands out, so the easiest game is the one in which nothing runs the player over. A disguised infantryman is refused as a crush target there as well. [Difficulty settings and handicaps](/systems/difficulty/) covers which house holds which slot.

Both tests reject a target beyond the distance rather than weighing crushing against firing on any other ground, so widening it makes computer-controlled crushers abandon their weapons over a longer reach.

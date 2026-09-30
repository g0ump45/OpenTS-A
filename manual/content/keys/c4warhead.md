---
key: C4Warhead
summary: The WarheadType behind damage the engine deals without a weapon to draw one from.
when_omitted:
  kind: value
  value: none
---

The engine reaches for this warhead wherever it applies damage that no weapon produced: a demolition charge going off on a structure, an infantryman poisoned by Tiberium or left standing on rock or water, a Tiberium field chain-reacting, a harvester exploding with its load, a laser fence energizing or being torn down over an occupied cell, a firestorm wall closing on something walking into it, and the [structure damage tick](/systems/power/#the-structure-damage-tick) a house takes while it is short of power.

Its [`Spread`](/keys/spread/) and animation lists therefore shape all of those at once. The demolition charge, the poisoning, the fence, and the firestorm wall pass their damage as forced, which skips the armor table and [`Immune=yes`](/keys/immune/) alike; the low-power tick, the chain reaction, and the harvester explosion are not forced, so only those three are shaped by the warhead's [`Verses`](/keys/verses/) table and blocked by immunity.

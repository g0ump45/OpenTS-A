---
key: CheckHeap
summary: Parsed heap check switch that the engine never acts on.
no_effect: true
see_also: ["Frame", "PrintCRC"]
when_omitted:
  kind: value
  value: "0"
---

The name promises a heap consistency check running alongside the game. A non-zero value does raise a global flag at the top of every game frame, but nothing anywhere reads that flag back. No gameplay path acts on it.

---
key: Burn
summary: Smudge type that belongs to the pool a scorch mark is chosen from.
see_also: [Crater, Width, Height, Scorch, Scorches]
when_omitted:
  kind: value
  value: "no"
---

The flag is the only thing that puts a smudge type into the scorch pool; [`Scorches`](/keys/scorches/) covers the list that looks as though it should and does not. The pool is gathered afresh every time the ground is scorched: every registered smudge type carrying the flag is offered the spot, those whose block will not fit there are dropped, and one of the survivors is picked at random. [`Height`](/keys/height/#scope-smudgetype) covers the fit test and the size grouping that narrows the survivors further.

```ini title="rules.ini"
[MYSCORCH]     ; example single-cell scorch mark
Burn=yes
```

Two things ask for a scorch. An animation asks through [`Scorch=yes`](/keys/scorch/) on its own type, and scorches on every occurrence unless it also carries [`Crater=yes`](/keys/crater/#scope-animtype), which turns each occurrence into a coin flip between the two pools. And a structure coming down asks twice over: once for the whole building, which happens only on a footprint of at least two cells by two and which requests the multiple-cell group directly, and once for each cell of the footprint, scattered a little and taking any smudge that fits. Each of those two requests is a coin flip against a crater, so half of them go to [`Crater`](/keys/crater/#scope-smudgetype) instead.

The two flags are independent on a smudge type: one carrying both belongs to both pools, and one carrying neither is registered, is given artwork, and is never placed by anything.

---
key: DamageLevels
summary: The number of damage stages a wall overlay passes through before it is removed.
see_also: ["system:walls-and-gates", "Strength"]
when_omitted:
  kind: value
  value: "1"
---

```ini title="art.ini"
[GAWALL]
DamageLevels=4
```

Each landed hit advances a wall cell by one stage; the segment is removed once the stage reaches this count. At the default of `1` the first landed hit removes the segment outright, so a wall only survives damage at all with a value above one. A segment with no connections to either side is removed one stage early, at the stage below this count.

Two other rules read the count. The [cascade](/systems/walls-and-gates/#stepping-through-the-stages) that carries damage into the neighboring segments fires when a cell reaches the stage below this count, and only when the count is above `2`. And a wall cell whose stored stage is exactly this count is a hole that infantry walk through unopposed — a state the damage path never leaves behind, since it removes the segment at that stage, but one a map's own overlay data can write directly.

Higher counts need matching artwork. The engine deletes an unconnected segment of a stock wall overlay that reaches a stage the shipped art does not cover, without any damage being applied; [the collapse table](/systems/walls-and-gates/#damage-stages-with-no-artwork) has the stages per overlay.

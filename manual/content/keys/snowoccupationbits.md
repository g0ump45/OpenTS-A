---
key: SnowOccupationBits
summary: Which of a cell's three infantry standing places a terrain object fills outside the temperate theater.
see_also: [TemperateOccupationBits, Foundation]
when_omitted:
  kind: value
  value: "7"
  note: All three standing places are filled, which is also the figure that makes the cell fully blocked.
---

The figure is read exactly as [`TemperateOccupationBits`](/keys/temperateoccupationbits/) is, and that page covers which bit fills which standing place, the whole-value test that decides whether infantry may path through the cell, and the way a larger object marks only the cell it is anchored to.

Which of the two is consulted comes from the scenario's theater. Marking the standing places uses the temperate figure in the temperate theater and this one otherwise; classing the cell as fully or partly blocked names the two theaters explicitly instead, so the two agree across the theaters the engine defines.

```ini title="rules.ini"
[MYROCK]                     ; example boulder that infantry can squeeze past
TemperateOccupationBits=4    ; only the south-east standing place is filled
SnowOccupationBits=4
```

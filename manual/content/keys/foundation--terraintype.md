---
key: Foundation
scope: terraintype
label: Terrain footprint
when_omitted:
  kind: value
  value: "1x1"
---

The value is one of the same 22 size names a structure uses, matched without regard to case, and anything else resolves to `1x1`. It picks the list of cells the terrain object stands on, which is what a vehicle tests before it may drive over the ground the object covers.

Terrain objects have their own table of footprints, and it is filled in only as far as the eighth name.

:::danger[A terrain object may not use a footprint past the eighth name]
Only `1x1`, `2x1`, `1x2`, `2x2`, `2x3`, `3x2`, `3x3` and `3x5` have cell lists. Every larger name selects a row the table never fills in. Those rows hold nothing but zeros and no end marker, so a terrain object given one claims its own top-left cell over and over — a hundred and forty times and more — and the scan then runs off the end of the table and reads memory that is not a cell list at all. The game normally crashes there.
:::

:::caution[On a terrain object 3x5 is a four-by-two block]
The eighth row holds four cells by two rather than the three by five its name promises, so a TerrainType given `Foundation=3x5` stands on a block of that shape instead.
:::

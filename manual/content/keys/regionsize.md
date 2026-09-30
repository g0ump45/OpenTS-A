---
key: RegionSize
summary: How large a piece of ground a generated map may hold at one height before it is broken up, as a figure from 0 to 100.
see_also: [Accessibility, Ruggedness, Biome]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

The generator carves the map into regions and then repeatedly splits any dry region that is too big, putting one half of each split at a new height. The cliff faces of a generated map are what those height changes leave behind, so the size limit is what decides how much cliff there is. [Map seed files](/formats/map-seed/) covers the section it is written in.

```ini title="map seed file"
[RandomMap]
RegionSize=20
```

A region is split while it holds more cells than a tenth of the playable area's width times its height, plus a hundredth of that product per point. The playable area holds about twice that product in cells, so the limit works out at roughly a twentieth of the map at `0` and a little over half of it at `100`. A region small enough to keep is marked so that it is never examined again, and a region holding water is never split at all.

:::caution[The setting does nothing at all on the tundra biome]
The splitting pass is skipped outright when [`Biome`](/keys/biome/) is `0`, the tundra, so on a tundra map the figure changes nothing whatever it is set to. On every other biome the figure stays live across its whole range: even at `100` the limit reaches only a little over half the map, so a single large region is still broken up.
:::

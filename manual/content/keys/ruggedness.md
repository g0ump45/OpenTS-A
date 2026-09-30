---
key: Ruggedness
summary: How hilly a generated map's ground is, as a figure from 0 to 100.
see_also: [RegionSize, Accessibility]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

The hills are laid down by a walk across the map that gives each cell a height drawn from the neighbors already settled, which is what makes the ground roll rather than step. The figure sets both how far each step of that walk may move — a tenth of a level plus a thousandth per point — and how widely the walk is allowed to wander around it. Cells beside a shoreline or a cliff face are pinned first and keep the height they were given, so the walk cannot raise a hill into the sea or bury an existing cliff. [Map seed files](/formats/map-seed/) covers the section it is written in.

```ini title="map seed file"
[RandomMap]
Ruggedness=40
```

The walk is skipped entirely unless the figure is at least `2`, so `0` and `1` both leave the ground exactly as the region pass left it. This is separate from the cliffs: [`RegionSize`](/keys/regionsize/) governs the sharp height changes between regions, and this figure the gentle relief laid over them afterward.

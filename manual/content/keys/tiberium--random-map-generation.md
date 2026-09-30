---
key: Tiberium
scope: random-map-generation
label: Tiberium richness
see_also: [TiberiumLayout, TiberiumWildlife, UseBlueTiberium, NumPlayers, "system:tiberium"]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

The figure sets how much tiberium each of the map's fields is grown to, not how many fields there are; [`TiberiumLayout`](/keys/tiberiumlayout/) governs the count. Each field is grown toward thirty cells per point plus a flat twenty-five hundred, multiplied by the player count and then divided between the fields, so a map built for more players is not left thinner. Each field then varies by a draw of up to a hundred cells either way, and a field whose draw takes it below nothing is skipped. [Map seed files](/formats/map-seed/) covers the section it is written in.

```ini title="map seed file"
[RandomMap]
Tiberium=60
TiberiumLayout=40
NumPlayers=4
```

A field is grown outward from its cell one cell at a time, taking the cheapest neighbor first so that the shape stays gathered but keeps a ragged edge. Ground that already carries tiberium is thickened rather than overwritten, and a growth that stalls early restarts from the same cell up to ten times.

The map generator dialog holds the figure to `1` through `100` rather than `0` through `100`, so the lowest figure it can produce still grows fields. Under the Firestorm addon the dialog also derives [`UseBlueTiberium`](/keys/usebluetiberium/) from this figure.

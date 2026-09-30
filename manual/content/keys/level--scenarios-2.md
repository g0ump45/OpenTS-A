---
key: Level
scope: scenarios-2
label: Map height offset
when_omitted:
  kind: value
  value: "0"
---

```ini title="map file"
[Map]
Level=1
```

The figure is added to every cell's height as the map dimensions are established, raising the whole playfield by that many levels. It shares only its spelling with the `[Lighting]` entry of the same name and has no bearing on lighting.

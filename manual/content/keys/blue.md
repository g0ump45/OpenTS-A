---
key: Blue
summary: The scenario's blue palette tint, where 1 leaves the blue channel unchanged.
see_also: [Red, Green, IonBlue, "system:ion-storms"]
when_omitted:
  kind: value
  value: "1"
---

```ini title="map file"
[Lighting]
Blue=.8
```

The value is stored in hundredths and tints the terrain palette every cell draws its ground through, from the moment the map loads; house color schemes are never tinted by these keys, and only an ion storm retints them. It is read before its ion counterpart in the same section and is what [`IonBlue`](/keys/ionblue/) falls back to.

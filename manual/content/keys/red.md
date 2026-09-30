---
key: Red
summary: The scenario's red palette tint, where 1 leaves the red channel unchanged.
see_also: [Green, Blue, IonRed, "system:ion-storms"]
when_omitted:
  kind: value
  value: "1"
---

```ini title="map file"
[Lighting]
Red=1
Green=.9
Blue=.8
```

The value is stored in hundredths and tints the terrain palette every cell draws its ground through as the map loads, so the tint is in place from the first frame rather than fading in. House color schemes are never tinted by these keys; only an ion storm retints them.

This value is read before its ion counterpart in the same section and is what [`IonRed`](/keys/ionred/) falls back to, so a map that gives only the three ordinary tint keys keeps its terrain coloring through [an ion storm](/systems/ion-storms/#lighting), while unit and building art picks the same tint up for the storm's duration.

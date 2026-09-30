---
key: AltImage
summary: The shape set a visceroid draws its attack animation from.
see_also: ["SmallVisceroid", "LargeVisceroid", "Image"]
when_omitted:
  kind: value
  value: ""
  note: No alternate shape set is bound, and the type draws from its ordinary artwork throughout.
---

The value is a filename without its extension, up to 23 usable characters. `.SHP` is appended and the shape set is fetched from the loaded archives as the section is read, so the artwork is bound once at load time rather than looked up again when it is drawn.

Only a [`SmallVisceroid=yes`](/keys/smallvisceroid/#scope-unittype) or [`LargeVisceroid=yes`](/keys/largevisceroid/#scope-unittype) UnitType ever draws from it, and only while its animation stage stands at 90 or above — the range a visceroid enters when it opens fire and leaves five frames later. Stages below 90 are its idle wandering and come from the ordinary [`Image`](/keys/image/#scope-aircrafttype) instead. Any other UnitType stores the name, fetches the artwork and never reaches a branch that draws it.

```ini title="rules.ini"
[MYVISCEROID] ; a UnitType registered in [VehicleTypes]
LargeVisceroid=yes
Image=MYVISC     ; idle frames
AltImage=MYVISCA ; attack frames, MYVISCA.SHP
```

The frame drawn is the stage less 90, so the shape set is read as eight five-frame runs in facing order starting from west: west at frames 0 through 4, then north-west, north, north-east, east, south-east, south and south-west, ending at frame 39.

A name that matches no file in the loaded archives leaves the type with no alternate shape set at all, and the attacking visceroid then draws nothing for those five frames while its position, weapon and damage carry on unchanged.

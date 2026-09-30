---
key: ShadowIndex
summary: Selects the voxel section a vehicle casts its shadow from.
see_also: ["Voxel"]
when_omitted:
  kind: value
  value: "0"
---

A `.vxl` model is a stack of numbered sections, and the shadow is rendered from one of them rather than from the whole model. Pointing this at the section that dominates the silhouette gives a vehicle a shadow shaped like that part instead of like its body.

```ini title="art.ini"
[MYTANK] ; the Image ID of a UnitType
Voxel=yes
ShadowIndex=1 ; the second section of MYTANK.VXL throws the shadow
```

Only a vehicle drawn from a voxel reads the setting. An aircraft always casts its shadow from section `0`, and nothing else in this scope casts a voxel shadow at all.

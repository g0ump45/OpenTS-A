---
key: VoxelBarrelScale
summary: The size a building's voxel barrel is drawn at, as a multiple of the model's own.
see_also: ["BarrelAnimIsVoxel", "VoxelBarrelFile", "VoxelBarrelOffsetToBarrelEnd"]
when_omitted:
  kind: value
  value: "1.0"
---

The scale is applied to the barrel model's own coordinates, inside the offsets that place it, so it resizes the barrel without moving the point it is mounted at. The muzzle rides with it: [`VoxelBarrelOffsetToBarrelEnd`](/keys/voxelbarreloffsettobarrelend/) is multiplied by the same figure, so a barrel drawn at three quarters size also fires from three quarters of the distance out. The three pivot offsets sit outside the scale and keep their length.

```ini title="rules.ini"
[MYARTILLERY] ; a BuildingType registered in [BuildingTypes]
BarrelAnimIsVoxel=yes
VoxelBarrelFile=MYARTBAR
VoxelBarrelScale=.75 ; three quarters of the size the model was built at
```

Only a [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building reads the setting.

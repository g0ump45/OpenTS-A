---
key: VoxelBarrelFile
summary: The voxel model a building's gun barrel is drawn from.
see_also: ["BarrelAnimIsVoxel", "TurretAnim", "VoxelBarrelScale", "TurretAnimIsVoxel"]
when_omitted:
  kind: value
  value: ""
---

The value is a file name without its extension: `<name>.VXL` is loaded as the barrel, with the `<name>.HVA` beside it. At most 15 characters are kept.

```ini title="rules.ini"
[MYARTILLERY] ; a BuildingType registered in [BuildingTypes]
TurretAnim=MYART_A ; an AnimType registered in [Animations]; carries no TUR
BarrelAnimIsVoxel=yes
VoxelBarrelFile=MYARTBAR ; the barrel is drawn from MYARTBAR.VXL
```

Only a [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building whose turret name yields no barrel name of its own consults the key. [`TurretAnim`](/keys/turretanim/) carrying `TUR` at its fifth character or later yields one — that `TUR` and everything after it replaced by `BARL` — and this setting is then ignored, as it is on a building that draws a voxel turret rather than a voxel barrel.

---
key: VoxelBarrelOffsetToBuildingPivotPoint
summary: Where a building's voxel barrel assembly is mounted on the structure.
see_also: ["BarrelAnimIsVoxel", "VoxelBarrelOffsetToRotatePivotPoint", "VoxelBarrelOffsetToPitchPivotPoint", "VoxelBarrelOffsetToBarrelEnd", "VoxelBarrelScale"]
when_omitted:
  kind: context-dependent
  note: No value is established. A BuildingType whose rules never assign the key keeps whatever the memory it was allocated from held.
---

Three whole numbers, `X,Y,Z`. A [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building places its barrel with four moves in order: out from the building by this offset, a turn to the building's facing, out by [`VoxelBarrelOffsetToRotatePivotPoint`](/keys/voxelbarreloffsettorotatepivotpoint/), an elevation to the barrel's pitch, and out by [`VoxelBarrelOffsetToPitchPivotPoint`](/keys/voxelbarreloffsettopitchpivotpoint/), with the model itself hanging off the end of that.

This one is applied before the turn, so it holds still while the gun swings and its axes are the map's rather than the gun's: `X` runs toward the lower right of the screen, `Y` toward the upper right, and `Z` upward. It is the offset that seats the whole assembly on the structure.

```ini title="rules.ini"
[MYARTILLERY] ; a BuildingType registered in [BuildingTypes]
BarrelAnimIsVoxel=yes
VoxelBarrelOffsetToBuildingPivotPoint=4,2,3 ; the mount, drawn an eighth of a cell out
VoxelBarrelOffsetToRotatePivotPoint=2,0,0
VoxelBarrelOffsetToPitchPivotPoint=15,0,-8
VoxelBarrelOffsetToBarrelEnd=350,75,0
```

The three pivot offsets are read at two scales. Drawing takes them as model units, of which there are 32 to a cell, while the firing point takes the same numbers as leptons, of which there are 256 — so this offset moves the drawn barrel eight times as far as it moves the shot.

:::danger[Every voxel barrel must set all four offsets]
The four pivot offsets have no starting value of their own: a BuildingType whose rules never assign one keeps whatever the memory it was allocated from held. A `BarrelAnimIsVoxel=yes` building that leaves one out draws its barrel, and creates its shells, at a point nothing in the files chose, and not necessarily the same point from one run to the next. A value written with fewer than three numbers leaves the components it did not supply in the same indeterminate state, this time from the parser's own scratch space.
:::

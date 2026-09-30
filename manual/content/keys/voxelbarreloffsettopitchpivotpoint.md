---
key: VoxelBarrelOffsetToPitchPivotPoint
summary: Where a building's voxel barrel sits once it has elevated.
see_also: ["BarrelAnimIsVoxel", "VoxelBarrelOffsetToBuildingPivotPoint", "VoxelBarrelOffsetToRotatePivotPoint", "VoxelBarrelOffsetToBarrelEnd", "PBarrelLength"]
when_omitted:
  kind: context-dependent
  note: No value is established. A BuildingType whose rules never assign the key keeps whatever the memory it was allocated from held.
---

Three whole numbers, `X,Y,Z`. A [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building places its barrel with four moves in order: out from the building by [`VoxelBarrelOffsetToBuildingPivotPoint`](/keys/voxelbarreloffsettobuildingpivotpoint/), a turn to the building's facing, out by [`VoxelBarrelOffsetToRotatePivotPoint`](/keys/voxelbarreloffsettorotatepivotpoint/), an elevation to the barrel's pitch, and out by this offset, with the model itself hanging off the end of that.

This one is applied after the elevation, so it rides up and down with the gun. `X` runs out along the pitched barrel, `Y` to its left and `Z` square to it — the place in the sequence that [`PBarrelLength`](/keys/pbarrellength/) occupies for an object with no voxel barrel, with two more components to it. The point it lands on is where the barrel model is hung, so it is the offset that decides which part of the barrel stays still while the rest swings.

```ini title="rules.ini"
[MYARTILLERY] ; a BuildingType registered in [BuildingTypes]
BarrelAnimIsVoxel=yes
VoxelBarrelOffsetToBuildingPivotPoint=4,2,3
VoxelBarrelOffsetToRotatePivotPoint=2,0,0
VoxelBarrelOffsetToPitchPivotPoint=15,0,-8 ; forward along the barrel and slightly below it
VoxelBarrelOffsetToBarrelEnd=350,75,0
```

The three pivot offsets are read at two scales. Drawing takes them as model units, of which there are 32 to a cell, while the firing point takes the same numbers as leptons, of which there are 256 — so this offset moves the drawn barrel eight times as far as it moves the shot.

:::danger[Every voxel barrel must set all four offsets]
The four pivot offsets have no starting value of their own: a BuildingType whose rules never assign one keeps whatever the memory it was allocated from held. A `BarrelAnimIsVoxel=yes` building that leaves one out draws its barrel, and creates its shells, at a point nothing in the files chose, and not necessarily the same point from one run to the next. A value written with fewer than three numbers leaves the components it did not supply in the same indeterminate state, this time from the parser's own scratch space.
:::

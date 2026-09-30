---
key: VoxelBarrelOffsetToBarrelEnd
summary: Where a building with a voxel barrel creates its shots.
see_also: ["BarrelAnimIsVoxel", "VoxelBarrelScale", "VoxelBarrelOffsetToPitchPivotPoint", "PrimaryFireFLH", "Burst"]
when_omitted:
  kind: context-dependent
  note: No value is established. A BuildingType whose rules never assign the key keeps whatever the memory it was allocated from held.
---

Three whole numbers, `X,Y,Z`, in leptons — 256 to a cell. The offset runs through the same placement the drawn barrel does, so it is measured on the pitched gun: `X` out along the barrel, `Y` to its left and `Z` square to it, with [`VoxelBarrelScale`](/keys/voxelbarrelscale/) multiplying all three before the pivot offsets carry it out to the structure. It is the only one of the four offsets that nothing draws.

On a [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building it replaces both points that [`PrimaryFireFLH`](/keys/primaryfireflh/) would otherwise fix: the mounting, where the projectile is created and the firing solution is measured from, and the muzzle, where the fire animation and beam appear. The two are the same point here, so the shot and its flash always leave the barrel together, and both rise as the gun elevates.

```ini title="rules.ini"
[MYARTILLERY] ; a BuildingType registered in [BuildingTypes]
BarrelAnimIsVoxel=yes
VoxelBarrelScale=.75
VoxelBarrelOffsetToBarrelEnd=350,75,0 ; drawn at .75, the muzzle sits 262 leptons out
```

A [`Burst`](/keys/burst/) weapon alternates: the first shot of a burst uses `Y` as written and the second mirrors it, giving a pair of muzzles either side of the barrel, while a third shot and any after it are centered on the barrel instead.

:::danger[Every voxel barrel must set all four offsets]
The four pivot offsets have no starting value of their own: a BuildingType whose rules never assign one keeps whatever the memory it was allocated from held. A `BarrelAnimIsVoxel=yes` building that leaves one out draws its barrel, and creates its shells, at a point nothing in the files chose, and not necessarily the same point from one run to the next. A value written with fewer than three numbers leaves the components it did not supply in the same indeterminate state, this time from the parser's own scratch space.
:::

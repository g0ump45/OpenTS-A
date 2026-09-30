---
key: SpawnCount
scope: voxelanimtype
label: Voxel meteor spawn count
see_also: ["Spawns", "IsMeteor"]
when_omitted:
  kind: value
  value: "0"
---

The number of child pieces is the sum of two independent picks from zero up to this figure, so it runs from none to twice the setting and averages the setting itself. A figure of zero or below spawns nothing, whatever [`Spawns`](/keys/spawns/#scope-voxelanimtype) names.

Only a meteor spawns at all. A piece without [`IsMeteor=yes`](/keys/ismeteor/#scope-voxelanimtype) never reaches the branch, and neither does a meteor that comes down low over water.

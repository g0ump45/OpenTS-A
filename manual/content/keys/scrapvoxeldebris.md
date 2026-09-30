---
key: ScrapVoxelDebris
summary: Parsed VoxelAnimType that the engine never uses.
no_effect: true
see_also: [ExplosiveVoxelDebris, TireVoxelDebris, DebrisTypes]
when_omitted:
  kind: value
  value: none
---

The name marks it as the scrap a destroyed vehicle sheds. Nothing reads the stored type. A type's destruction debris comes from its own [`DebrisTypes`](/keys/debristypes/) list, as [`ExplosiveVoxelDebris`](/keys/explosivevoxeldebris/) describes.

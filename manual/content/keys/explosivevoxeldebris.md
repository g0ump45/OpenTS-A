---
key: ExplosiveVoxelDebris
summary: Parsed VoxelAnimType list that the engine never uses.
no_effect: true
see_also: [ScrapVoxelDebris, TireVoxelDebris, DebrisTypes]
when_omitted:
  kind: value
  value: ""
---

The name marks it as the flying wreckage a destroyed vehicle throws off. Nothing reads the stored list, and neither does anything read the two single-type settings [`ScrapVoxelDebris`](/keys/scrapvoxeldebris/) and [`TireVoxelDebris`](/keys/tirevoxeldebris/) beside it.

Destruction debris is chosen per type instead. A type declaring [`MaxDebris`](/keys/maxdebris/) above zero throws pieces from its own [`DebrisTypes`](/keys/debristypes/) list, taking up to the matching [`DebrisMaximums`](/keys/debrismaximums/) figure from each entry in turn until the `MaxDebris` budget runs out. A type with a budget and no list of its own throws up to that many [`MetallicDebris`](/keys/metallicdebris/) animations instead.

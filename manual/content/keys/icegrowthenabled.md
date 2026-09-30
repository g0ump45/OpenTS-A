---
key: IceGrowthEnabled
summary: Allows ice sheets to creep outward and cracked ice to refreeze.
see_also: [TiberiumGrowthEnabled, VeinGrowthEnabled, IceSolidifyFrameTime]
when_omitted:
  kind: value
  value: "yes"
---

```ini title="map file"
[Basic]
IceGrowthEnabled=no
```

The switch gates two passes. One thickens the thin tiles at the fringe of a sheet into full ice, which is how a sheet creeps outward over the course of a mission; it runs on the scenario's ice-growth timer rather than every frame. The other runs once a frame and heals ice that something cracked by crossing it, once its delay has elapsed, taking the cracked neighbors with it.

Both passes also require the snow theater, so the switch changes nothing on a temperate map. Turning it off leaves cracked ice cracked for the rest of the mission. The [Ice growth](/mapping/actions/taction-ice-growth/) trigger action writes the same switch while the scenario is running.

---
key: Theater
scope: aircrafttype
label: Theater-specific artwork
see_also: ["NewTheater", "Image", "Voxel"]
when_omitted:
  kind: value
  value: "no"
---

The shape file keeps the Image ID as its name and exchanges its extension for the theater's own: `.TEM` in temperate and `.SNO` in snow. Nothing else about the name changes, and there is no fallback to `.SHP` on this path — a theater with no file of its own leaves the type with no shape.

```ini title="art.ini"
[MYROCK] ; the Image ID of a TerrainType
Theater=yes ; draws MYROCK.TEM or MYROCK.SNO, never MYROCK.SHP
```

The flag is tested before [`NewTheater`](/keys/newtheater/) and wins outright, so a type marked with both is only ever renamed by extension. A [`Voxel=yes`](/keys/voxel/) AircraftType, InfantryType or UnitType has no shape to rename at all; a BuildingType resolves and loads a theater-named shape either way.

:::caution[Only some of these types keep the substitution]
An AircraftType, InfantryType, or UnitType looks its plain `<Image ID>.SHP` up again immediately after the flag has been applied and keeps whatever that returns, so the theater file never reaches it. Those three, a BulletType, a ParticleType, a ParticleSystemType and a VoxelAnimType also leave their artwork as it stands when the scenario theater changes, while a BuildingType, OverlayType, SmudgeType, or TerrainType resolves the name again against the new theater.
:::

---
key: NewTheater
scope: aircrafttype
label: Theater artwork naming
see_also: ["Theater", "Image", "Voxel"]
when_omitted:
  kind: value
  value: "no"
---

The file keeps its `.SHP` extension and the second letter of its name is rewritten instead, to the theater's [`ImageLetter`](/keys/imageletter/): `T` in temperate and `A` in snow. The rewrite is applied only where the Image ID's second letter is already the image letter of some declared theater, and the comparison ignores case. Any other name is left exactly as written, so the flag does nothing for it — which is how the civilian artwork that carries the flag in error, `CITY`, `ABAN`, `BBOARD`, `MWAR` and `OBL1`, escapes being renamed.

```ini title="art.ini"
[GACNST] ; the Image ID of a BuildingType
NewTheater=yes ; draws GTCNST.SHP in temperate and GACNST.SHP in snow
```

[`Theater=yes`](/keys/theater/) is tested first and wins, so a type marked with both only ever swaps its extension. A [`Voxel=yes`](/keys/voxel/) AircraftType, InfantryType or UnitType has no shape to rename; a BuildingType resolves and loads a theater-named shape either way.

:::caution[Only some of these types keep the rewrite]
An AircraftType, InfantryType, or UnitType looks its unrewritten `<Image ID>.SHP` up again immediately after the rename and keeps whatever that returns. Those three, a BulletType, a ParticleType, a ParticleSystemType and a VoxelAnimType also leave their artwork as it stands when the scenario theater changes — as do a SmudgeType and a TerrainType, whose theater pass handles [`Theater`](/keys/theater/) alone.
:::

:::note[A building is renamed whether or not the flag is set]
A BuildingType runs its shape, its buildup, and its door, deploy, bib, and Z-overlay animations through the same rewrite every time its rules section is read. The flag is what makes a building resolve those names again against a new theater.
:::

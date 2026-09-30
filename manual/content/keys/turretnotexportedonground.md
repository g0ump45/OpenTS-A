---
key: TurretNotExportedOnGround
summary: Pivots a building's voxel barrel about its firing offset instead of about the model origin.
see_also: ["PrimaryFireFLH", "TurretAnimIsVoxel", "Voxel"]
when_omitted:
  kind: value
  value: "no"
---

Only a [`TurretAnimIsVoxel=yes`](/keys/turretanimisvoxel/) building reads the setting, on the path that draws its voxel barrel.

Cleared, the barrel model is pitched about its own origin and the firing offset swings around with it, which is what artwork exported with the barrel's pivot resting on the ground expects. Set, the barrel is pitched about the point the `X` and `Z` components of [`PrimaryFireFLH`](/keys/primaryfireflh/) name, so that point holds still while the barrel elevates and artwork exported with its pivot already raised lines up again. The `Y` component takes no part either way.

```ini title="art.ini"
[MYTURRET] ; the Image ID of a BuildingType
PrimaryFireFLH=90,0,110
TurretNotExportedOnGround=yes ; the barrel elevates around 90,-,110
```

A turreted vehicle's voxel barrel is always pitched the second way, whatever this setting says; one whose turret model is missing pitches its barrel the first way instead.

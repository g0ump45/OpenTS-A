---
key: RadarInvisible
scope: aircrafttype
label: Object types
no_effect: true
when_omitted:
  kind: context-dependent
  note: A BulletType, OverlayType, SmudgeType, TerrainType or VoxelAnimType section starts at yes. Every other object type starts at no.
---

Keeping an object off the radar without hiding it on the map is the work of the `RADAR_INVISIBLE` [veteran ability](/systems/veterancy/#abilities), which comes with rank rather than from a type. The two settings the [radar test](/systems/cloaking/#on-the-radar) does read are [`Invisible`](/keys/invisible/) and [`RadarVisible`](/keys/radarvisible/).

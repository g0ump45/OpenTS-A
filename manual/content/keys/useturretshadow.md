---
key: UseTurretShadow
summary: Parsed shadow flag that the engine never uses.
no_effect: true
see_also: ["Turret", "ShadowIndex", "Voxel"]
when_omitted:
  kind: value
  value: "no"
---

No drawing path consults the flag. A [`Turret=yes`](/keys/turret/) vehicle drawn from shape artwork casts its shadow from the frame at its own body frame plus half the frame count of its shape file, whatever this is set to, so the shadow follows the hull rather than the gun either way.

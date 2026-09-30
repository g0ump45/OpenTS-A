---
key: Damage
scope: voxelanimtype
label: Voxel animation damage
see_also: ["DamageRadius", "Warhead"]
when_omitted:
  kind: value
  value: "0"
---

Sets the raw damage a voxel animation applies at each bounce and when it expires. Its [`Warhead`](/keys/warhead/) adjusts that value independently for every object reached, so each damage calculation begins with the configured figure.

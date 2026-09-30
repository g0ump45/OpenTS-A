---
key: Warhead
scope: voxelanimtype
label: Voxel debris warhead
see_also: ["Damage", "DamageRadius", "ExpireAnim"]
when_omitted:
  kind: value
  value: none
---

The warhead carries [`Damage`](/keys/damage/#scope-voxelanimtype) at both points a voxel animation deals it: to each object standing within [`DamageRadius`](/keys/damageradius/#scope-voxelanimtype) of a bounce, and as the blast where the piece's life ends. Its armor multipliers and its [`Spread`](/keys/spread/#scope-warheadtype) decide what that damage is worth against a given target, and its [`Bright`](/keys/bright/#scope-warheadtype) flag decides whether the impact throws a flash of light.

A piece with no warhead named deals nothing at either point: the blast is refused before it starts, and a bounce skips its damage pass. The piece still bounces, plays its effects, and craters or seeds the ground it lands on. Its stored [`Damage`](/keys/damage/#scope-voxelanimtype) is left unchanged.

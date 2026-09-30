---
key: StartSound
scope: voxelanimtype
label: Voxel debris creation sound
see_also: ["BounceSound", "ExpireSound", "IsMeteor", "AttachedSystem"]
when_omitted:
  kind: value
  value: none
---

The sound plays once, as the piece is created, at the coordinate the piece was asked for. For a meteor that is the coordinate it is aiming at rather than the point it actually starts from, so the sound arrives at the landing site a whole flight ahead of the meteor.

A value naming no registered sound leaves whatever was set before in place.

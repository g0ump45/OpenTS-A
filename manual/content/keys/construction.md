---
key: Construction
summary: Parsed sound that the engine never plays.
no_effect: true
see_also: [BuildingSlam, BuildingDrop, CrumbleSound]
when_omitted:
  kind: value
  value: none
---

The name promises a sound for a structure going up. The value is resolved against the sound registry and stored, and no gameplay path reads the slot back. An unregistered sound name is not even stored; the slot keeps whatever it already held.

The sounds a structure does make as it appears belong to other settings: [`BuildingSlam`](/keys/buildingslam/) when the player places one, [`BuildingDrop`](/keys/buildingdrop/) when a construction vehicle deploys into one.

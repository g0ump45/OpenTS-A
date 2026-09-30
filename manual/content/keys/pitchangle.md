---
key: PitchAngle
summary: The angle in degrees an aircraft drops its nose by while it is flying fast enough.
see_also: ["PitchSpeed", "RollAngle", "IsDropship"]
when_omitted:
  kind: value
  value: "20"
---

The value is written in degrees and converted to radians as it is read. Only the fly locomotor consults it, and for anything but a dropship only while the aircraft is off the ground.

An ordinary aircraft holds this nose-down attitude for as long as its throttle is above [`PitchSpeed`](/keys/pitchspeed/), and levels off below that. A [`HunterSeeker=yes`](/keys/hunterseeker/) type is excluded from the nose-down and always flies level. An aircraft that has been rocked by a nearby jolt adds the angle on top of whatever the jolt is doing to it.

An [`IsDropship=yes`](/keys/isdropship/) type ignores that rule entirely and treats the figure as a ceiling instead: it tips over gradually as it comes in to land, reaching the full angle four tenths of the way through its [`SlowdownDistance`](/keys/slowdowndistance/), and once down it levels off again at 0.02 radians per frame.

:::caution[Writing `-1` is the same as leaving the key out]
The read uses `-1` as its own marker for a missing key, so `PitchAngle=-1` leaves the stored 20 degrees in place. Write `PitchAngle=0` to make a type fly level.
:::

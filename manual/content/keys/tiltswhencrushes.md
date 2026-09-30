---
key: TiltsWhenCrushes
summary: Makes a vehicle lurch forward as it crushes a sandbag wall.
see_also: ["Crusher"]
when_omitted:
  kind: value
  value: "yes"
---

The drive and mech locomotors both check the flag where they mark a vehicle as crushing — the mech at the cell it is about to enter, the drive at the cell it has just entered and only while the hull is already rocking: that cell holds sandbag wall and the vehicle is a [`Crusher=yes`](/keys/crusher/) or has earned the crusher ability. With the flag set the hull is given a forward tilt at that moment — a heavier one under the drive locomotor than under the mech. Cleared, the wall still goes and the vehicle is still marked as crushing, which holds an [`Accelerates=yes`](/keys/accelerates/) vehicle to a fifth of its speed while it goes through, but the hull stays level.

Only sandbag wall triggers it. Every other crushable overlay rocks the vehicle through the ordinary crush path, which does not consult this flag. The stock rules clear it on one type, the Mammoth Mk. II.

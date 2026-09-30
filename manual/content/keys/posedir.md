---
key: PoseDir
summary: Facing an aircraft parks at when it has nothing else to line up with.
see_also: [PadAircraft, HoverPad, SeparateAircraft]
when_omitted:
  kind: value
  value: "0"
---

```ini title="rules.ini"
[AudioVisual]
PoseDir=0
```

Two paths read it, and they disagree about what the number means.

The placement path treats it as a 256-step direction, where 0 is north and each step is a little over one and a third degrees, so 64 is east and 128 is south. It supplies the facing an aircraft is given as it is put on the map: the free helicopter a helipad gets when it is built, and an aircraft leaving the factory it was built at, whether it lands on the pad or is pushed to a nearby cell because an ion storm is running.

The landing path treats the same number as an eight-step compass facing instead, where 1 is northeast and 4 is south. It supplies the direction an aircraft turns its body toward as it settles on its destination with nothing to aim at, or while strafing. That direction is settled in order:

1. an aircraft in radio contact with a helipad or a vehicle copies that object's facing;
2. a loaded aircraft keeps the heading it already has;
3. anything else takes this value.

At the default of `0` the two agree, since north is zero on both scales. Any other value points the two paths in different directions, and because the landing path keeps only the low three bits of the number, values `8`, `16`, `24` and so on all read as north there while the placement path reads each of them as a different heading.

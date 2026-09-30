---
key: PrimaryFirePixelOffset
summary: The screen offset a building's shots leave from, in place of its firing offsets.
see_also: ["PrimaryFireFLH", "SecondaryFirePixelOffset", "BarrelAnimIsVoxel", "TurretAnimX", "Primary"]
when_omitted:
  kind: value
  value: 65535,65535
---

Two whole numbers, `X,Y`, in screen pixels from the point the building's artwork is drawn at: a positive `X` moves right and a positive `Y` down. Any pair other than `65535,65535` replaces both the mounting — where the projectile is created and the firing solution is measured from — and the muzzle, where the fire animation and beam appear, and moves the point the building measures its aim from with them. The replacement covers every weapon the building fires, not only the first.

```ini title="art.ini"
[MYOBELISK] ; the Image ID of a BuildingType
PrimaryFirePixelOffset=2,-38 ; the beam leaves 38 pixels above the draw point
```

The offset is projected back onto the ground rather than applied as a height, so the shot appears exactly that many pixels from the artwork, at the building's own height. It also outranks the barrel: a [`BarrelAnimIsVoxel=yes`](/keys/barrelanimisvoxel/) building with this set fires from the fixed screen point rather than from the end of its barrel, and [`PrimaryFireFLH`](/keys/primaryfireflh/) covers the offsets it displaces.

:::danger[Write both numbers]
The test that switches the offset on is against the exact pair `65535,65535`, and a value with only one number leaves the second unset: the offset is then whatever the parsing scratch space held, which need not be the same figure from one run to the next or on two machines playing together.
:::

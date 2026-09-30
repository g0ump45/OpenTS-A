---
key: Voxel
summary: Draws the type from a voxel model rather than from a shape file.
see_also: ["Image", "ShadowIndex", "Turret", "Theater"]
when_omitted:
  kind: value
  value: "no"
---

A TechnoType or a BulletType marked here loads `<Image ID>.VXL` together with its `<Image ID>.HVA` motion file.

```ini title="art.ini"
[MYTANK] ; the Image ID of a UnitType
Voxel=yes ; draws MYTANK.VXL and MYTANK.HVA
```

A [`Turret=yes`](/keys/turret/) vehicle also picks up `<Image ID>TUR` for its turret and `<Image ID>BARL` for its barrel, each as a `.VXL` and `.HVA` pair. A voxel type that is not a vehicle looks for both pairs whether or not it carries a turret. A companion `.VXL` that is not there is not drawn. A companion `.HVA` that is not there is treated as a load failure and throws the whole voxel set away, leaving the type with no model at all.

Setting the flag also skips the shared shape fetch — the one [`Theater=yes`](/keys/theater/) and [`NewTheater=yes`](/keys/newtheater/) rename the file for. A BulletType is the exception: it makes that fetch on its own account unless it is [`Inviso=yes`](/keys/inviso/), so a voxel projectile keeps its shape as well.

:::caution[A model that fails to load leaves nothing behind]
A vehicle marked as a voxel is drawn from its model or not at all. There is no fallback to the shape file, so a misspelled Image ID or a missing `.VXL` leaves the vehicle invisible while it goes on fighting.
:::

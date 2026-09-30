---
key: Speed
scope: weapontype
label: Projectile launch speed
when_omitted:
  kind: value
  value: "0"
---

The figure is scaled exactly as an object's top speed is: clamped to the range 0 to 100, mapped onto the internal 0-to-255 scale, and with `-1` read as a missing key rather than as a value. It is the cruising speed a homing projectile works up to from a launch speed of `1`, and the launch speed of an unguided one, capped there at half the distance to the target.

:::caution[An unguided weapon's figure is discarded]
Once every weapon and projectile section in a file has been read, the launch speed of any weapon whose [`Projectile=`](/keys/projectile/) carries [`ROT=0`](/keys/rot/#scope-bullettype) is worked out afresh from that weapon's [`Range=`](/keys/range/) and the gravity the projectile falls under, so that the shot reaches the full range. Whatever was written here is overwritten. Only a weapon whose projectile homes, or which names no projectile at all, keeps the figure.
:::

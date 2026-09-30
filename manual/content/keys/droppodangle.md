---
key: DropPodAngle
summary: Drop-pod descent angle in radians, clamped to 22.5-67.5 degrees when rules load.
see_also: [DropPodHeight, DropPodSpeed, "system:drop-pods"]
---

The angle divides a pod's movement between horizontal and vertical travel. It also controls how far from the landing cell the pod begins: the horizontal offset is `DropPodHeight / tan(DropPodAngle)`.

Values read from `[General]` are clamped to `pi/8` through `3*pi/8` radians (22.5-67.5 degrees). A smaller angle produces a longer, shallower approach; a larger angle produces a shorter, steeper approach.

```ini title="rules.ini"
[General]
DropPodAngle=0.785398   ; 45 degrees
```

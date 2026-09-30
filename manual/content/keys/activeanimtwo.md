---
key: ActiveAnimTwo
summary: The animation the structure runs in its second active slot.
see_also: ["ActiveAnim", "ActiveAnimTwoDamaged", "ActiveAnimTwoX", "ActiveAnimTwoY", "ActiveAnimTwoYSort", "ActiveAnimTwoZAdjust", "ActiveAnimTwoPowered", "ActiveAnimTwoPoweredLight", "TurretAnimIsExclusive"]
when_omitted:
  kind: value
  value: ""
---

[Building animations](/systems/building-animations/) covers the slot mechanism all four share. The second slot is the one a charging turret takes over: on a [`TurretAnimIsExclusive=yes`](/keys/turretanimisexclusive/) structure it is destroyed as the turret starts charging, not left running while the turret is charged or charging, and created again once the charge is spent.

Installing an [upgrade](/keys/upgrades/) is the exception. A plug that brings a damaged structure back to full strength restarts every empty active slot without consulting the turret, so an exclusive turret that is charging at that moment ends up running this slot alongside its own animation until the charge is spent.

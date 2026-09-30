---
key: EMPulseCannon
summary: Lets a BuildingType serve as the launch site of an EMPulse superweapon.
see_also: ["system:emp-pulse"]
when_omitted:
  kind: value
  value: "no"
---

The superweapon [picks the owner's nearest powered cannon and hands it the target](/systems/emp-pulse/#em-pulse-cannon-superweapon). The flag otherwise disarms the building: it is refused permission to fire and is skipped by the automatic target search, so its primary weapon is reached only through the missile mission the launch assigns.

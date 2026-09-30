---
key: TurretAnimDamaged
summary: The turret animation a building shows once it is damaged.
see_also: ["TurretAnim", "TurretAnimIsVoxel", "ConditionYellow"]
when_omitted:
  kind: computed
  note: The `TurretAnim` value, copied across whenever nothing has set this key.
---

Every animation a building is running is restarted in its damaged form as the structure's health falls to [`ConditionYellow`](/keys/conditionyellow/) or below, and in its healthy form again once repairs lift it back above. The replacement takes over at the stage the previous animation had reached, so a turret part way through its sequence does not start again from the beginning.

The value is an AnimType ID, as [`TurretAnim`](/keys/turretanim/) is. A [`TurretAnimIsVoxel=yes`](/keys/turretanimisvoxel/) building has no turret animation and takes its model name from `TurretAnim` alone, so nothing there reads this key.

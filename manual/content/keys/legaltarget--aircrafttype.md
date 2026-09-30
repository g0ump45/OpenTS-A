---
key: LegalTarget
scope: aircrafttype
label: Object targetability
see_also: ["system:target-selection"]
when_omitted:
  kind: context-dependent
  note: Most object types start targetable. A BulletType, SmudgeType, TerrainType or VoxelAnimType starts untargetable instead, and a TerrainType is forced back to targetable by IsVeinhole=yes after its section is read.
---

A type set to `no` is rejected by every automatic target scan, and pointing at one of its objects offers no attack cursor. Holding the force-fire modifier bypasses the cursor test, so a player can still order a shot at it by hand, and a scan by an object that has already been given such a target is unaffected — the rejection happens while candidates are being weighed, not while a shot is being taken.

```ini title="rules.ini"
[MYPROP] ; example BuildingType used as scenery
LegalTarget=no
```

Tree targeting is a separate allowance: with `[CombatDamage] TreeTargeting=yes` a player may point at a TerrainType whatever this setting says.

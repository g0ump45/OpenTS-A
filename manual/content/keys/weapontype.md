---
key: WeaponType
summary: The WeaponType a missile silo launches for this superweapon.
see_also: ["system:superweapons"]
when_omitted:
  kind: value
  value: none
---

The silo takes the projectile, warhead, maximum speed and projectile range from this weapon and launches them with [a hard-coded strength of 200](/systems/superweapons/#multi-missile-and-chem-missile). Nothing else reads the value: the ion cannon, the EM pulse, the firestorm, the hunter seeker and the drop pods all deliver payloads of their own, and a one-time missile is built from the hard-coded weapons `MultiLauncher` and `ChemLauncher` regardless of what is set here.

:::danger[The silo does not look the weapon up by section]
A silo records the *behavior* number of the weapon that ordered the launch and then reads the declared superweapon list at that position. The weapon it ends up firing is this key of whichever section stands there, which is the ordering section only while `[SuperWeaponTypes]` is declared in exactly the behavior order the shipped list uses.
:::

---
key: SuperWeapon2
summary: A second superweapon a standing structure of this type grants its owner.
see_also: [SuperWeapon, "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

Everything [`SuperWeapon=`](/keys/superweapon/) does, this does independently and at the same time: the availability scan, the removal scan, the [`AuxBuilding=`](/keys/auxbuilding/) test, the plug slots and the missile-silo match all read both keys. A structure may therefore grant two weapons, as the stock Nod missile silo does with the multi missile and the chem missile. There is no third slot.

```ini title="rules.ini"
[NAMISL]        ; Missile Silo
SuperWeapon=MultiSpecial
SuperWeapon2=ChemicalSpecial
NukeSilo=yes
```

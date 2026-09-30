---
key: TurretChargeAnimRate
summary: The delay between frames of a building's turret animation while its weapon charges.
see_also: ["TurretAnim", "TurretAnimIsExclusive", "Charges", "ChargeAnim"]
when_omitted:
  kind: value
  value: "3"
---

The value is the number of game frames each frame of the charge sequence is held for, and there are 15 game frames to the second. Charging begins when a building whose primary weapon is [`Charges=yes`](/keys/charges/) has a target, its house has full power and it is switched on; the weapon is charged once the sequence reaches the last looping frame of the [`TurretAnim`](/keys/turretanim/) animation, or stage 12 — the thirteenth frame counting from zero — if the animation has since ended. The rate therefore sets how long the wind-up takes, and the weapon is refused a shot until it finishes.

```ini title="rules.ini"
[MYOBELISK] ; a BuildingType registered in [BuildingTypes]
Primary=MyChargeLaser  ; a WeaponType with Charges=yes
TurretAnim=MYOBEL_C    ; an AnimType registered in [Animations]
TurretChargeAnimRate=1 ; one game frame per frame of the wind-up
```

Losing the target, losing power or being switched off empties the charge again and stops the sequence, and the wind-up starts over from the beginning when the building next takes aim.

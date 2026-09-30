---
key: TeslaCharge
summary: Sound a structure makes as its electric weapon begins charging.
see_also: [TeslaZap, Charges, TurretChargeAnimRate]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
TeslaCharge=TESLCHG ; a sound ID registered in SOUND.INI
```

The sound is played from the structure's own position on the pass that starts the charge, and one charge covers one shot. The structure must carry a primary weapon marked [`Charges=yes`](/keys/charges/), have finished its build-up, be switched on with a target, and belong to a house at full power; it must also be past its reload delay and hold a legal firing solution on that target with one of its two weapons. Nothing about the sound is tied to the player: an enemy structure charging within earshot is heard.

Losing power, being switched off or losing the target discharges the turret in silence, and a structure that is already charged does not sound again until it has fired and started over.

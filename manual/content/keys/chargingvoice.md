---
key: ChargingVoice
summary: The EVA line spoken as the superweapon starts charging.
see_also: ["system:superweapons"]
when_omitted:
  kind: value
  value: none
---

The line is spoken only for the local player's own weapon, and only where a charge is started rather than resumed. Three starts qualify:

- a structure or a plug first grants the weapon;
- a repeating weapon discharges and begins its next charge;
- a [`Type=ChemMissile`](/keys/type/) weapon is started by its house's [weed storage filling](/systems/superweapons/#manual-control).

A weapon coming back from suspension and a [`UseChargeDrain=yes`](/keys/usechargedrain/) weapon returning to charging both pass through silently, as does every weapon granted by a trigger action or a crate. An unrecognized speech name is not rejected; it leaves the weapon with no line.

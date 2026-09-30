---
key: DeploysInto
summary: The BuildingType a vehicle turns into when it is given the deploy order.
see_also: ["UndeploysInto", "BaseUnit"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[MCV]
DeploysInto=GACNST ; GDI Construction Yard
```

Naming a type is one of the three things that give a vehicle the deploy cursor — the others are carrying cargo and being a mobile EM pulse — and the deploy order runs in three steps. The vehicle first tests whether the structure may legally be placed: a house under player control that fails gets the "cannot deploy here" speech and the order is dropped, while a computer house instead clears the cell for the next attempt. It then turns to the facing the structure deploys at, holding the order until it gets there. Only then is the structure created, on the mission that plays its buildup, and the vehicle is removed.

Where the structure lands depends on the structure, not on the vehicle: one that is really a deployed vehicle — the sensor array, tick tank, ICBM launcher, artillery, mobile stealth generator, Juggernaut, core defender and limpet mine flags each make one — is placed on the vehicle's own cell, and every other structure is placed one cell to the north-west. The new structure inherits the house it belongs to, the side its artwork follows, its selection group, its crew's experience and any limpet drone clamped to it, and anything that was shooting at the vehicle transfers its target to the structure.

Three other paths read the value on a UnitType. A house's [`BuildLimit`](/keys/buildlimit/) count for the vehicle adds the number of structures of the named type the house already owns, so deploying an MCV does not free a slot to build another. A vehicle that deploys is treated as slow-witted for the purpose of a team that guards its slower members. And a human player's vehicle that deploys into an [`Artillary=yes`](/keys/artillary/) structure never retaliates on its own.

A name that matches no registered BuildingType registers a new, unconfigured structure under that name rather than failing. The values `none` and `<none>` resolve to nothing at all, exactly as if the key had been left out.

The key is accepted in an AircraftType, BuildingType, InfantryType or UnitType section, but only a vehicle ever deploys.

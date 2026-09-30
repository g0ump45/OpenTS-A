---
key: AuxSound1
summary: The sound a structure makes as its build-up starts, and the sound a flying object makes as it takes off.
see_also: [AuxSound2, DeploySound, Locomotor]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[MYHELI] ; an AircraftType registered in [AircraftTypes]
AuxSound1=MYHELI_Takeoff ; a sound ID registered in SOUND.INI
```

Two unrelated paths read the same slot:

- A **structure** plays it at its own position the moment its build-up animation begins, whichever house owns it.
- An object flown by the [flyer locomotor](/keys/locomotor/) plays it at its own position when it lifts off, unless it is stunned at the time.

Nothing else reads the slot, so on a ground vehicle or an infantryman the setting is inert.

:::caution[A structure's `DeploySound` wins]
[`DeploySound`](/keys/deploysound/#scope-buildingtype) is stored in this same slot and is read afterward, so a BuildingType that sets both keeps only `DeploySound`. Setting them to different sounds does not give a structure two.
:::

A name that matches no registered sound leaves the previous value in place rather than clearing it, so a misspelling here is silent in a different way from a misspelling in a voice list.

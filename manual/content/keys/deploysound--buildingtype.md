---
key: DeploySound
scope: buildingtype
label: Structure build-up sound
see_also: [AuxSound1, UndeploySound]
when_omitted:
  kind: value
  value: none
  note: The slot holds whatever `AuxSound1` put there, and nothing at all when that key is unset too.
---

```ini title="rules.ini"
[MYSILO] ; a BuildingType registered in [BuildingTypes]
DeploySound=MYSILO_Buildup ; a sound ID registered in SOUND.INI
```

A structure plays this at its own position the moment its build-up animation begins, whichever house owns it.

:::caution[It replaces `AuxSound1`]
The key stores into the same slot as [`AuxSound1`](/keys/auxsound1/) and is read after it, so a BuildingType that sets both keeps only this one. A name that matches no registered sound leaves the slot alone rather than clearing it, which means a misspelling here quietly leaves an `AuxSound1` in place.
:::

---
key: AmbientChangeRate
summary: Minutes between one step of the ambient light fade and the next.
see_also: [AmbientChangeStep, Ambient, IonAmbient, "system:ion-storms"]
when_omitted:
  kind: value
  value: ".2"
---

```ini title="rules.ini"
[AudioVisual]
AmbientChangeRate=.2
```

The figure is converted at 900 frames to the minute, so `.2` waits 180 frames between steps. Together with [`AmbientChangeStep`](/keys/ambientchangestep/) it fixes how long the map takes to reach a new ambient level, whether the change came from a scripted action or from [an ion storm](/systems/ion-storms/#the-ambient-ramp).

:::caution[Zero stops the fade entirely]
The step is guarded on a non-zero rate. At `0` the current ambient level never moves again, so a scripted lighting change and a storm's darkening are both stored and never shown.
:::

The [Set ambient rate...](/mapping/actions/taction-set-ambient-rate/) trigger action overwrites this value in the loaded rules, and the overwrite outlives the trigger that made it.

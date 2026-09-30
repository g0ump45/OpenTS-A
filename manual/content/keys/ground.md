---
key: Ground
summary: A flat darkening subtracted from every cell's brightness, as a fraction of full light.
see_also: [Level, IonGround, "system:ion-storms"]
when_omitted:
  kind: value
  value: "0"
  note: The engine starts each scenario with a tenth of full light here, but the fallback used when the key is absent divides two whole numbers and truncates to zero, so an omitted key stores zero rather than that tenth.
---

```ini title="map file"
[Lighting]
Ground=.1
Level=.016
```

Cell brightness is the ambient level, plus [`Level`](/keys/level/) for each height level the cell stands above the ground, minus this figure. Raising it darkens the whole map evenly on top of whatever [`Ambient`](/keys/ambient/) sets.

:::danger[Omitting the key is not the same as leaving it alone]
The value the engine starts with cannot survive omission: the absent-key fallback is computed as a whole-number division and always truncates a fraction below `1` to `0`. A scenario that wants any ground darkening has to state it, and [`IonGround`](/keys/ionground/) has to be stated as well or it collapses the same way.
:::

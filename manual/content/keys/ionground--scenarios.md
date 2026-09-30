---
key: IonGround
scope: scenarios
label: Scenario lighting
see_also: [Ground, IonLevel, "system:ion-storms"]
when_omitted:
  kind: context-dependent
  note: This scenario's Ground value truncated to a whole number, because the fallback divides two whole numbers. Every Ground value below 1 therefore yields 0.
---

```ini title="map file"
[Lighting]
Ground=.1
IonGround=.1
```

While a storm runs, this figure replaces [`Ground`](/keys/ground/) as the flat amount subtracted from every cell's brightness. The swap happens on the frame the storm breaks and reverses on the frame it ends, with no fade in either direction.

:::danger[The fallback cannot reproduce an ordinary ground value]
Leaving this key out does not copy `Ground` across: the fallback is a whole-number division that truncates any fraction below `1` to `0`. A map that sets `Ground=.1` and omits this key loses its ground darkening for the length of every storm. State the value outright to keep it.
:::

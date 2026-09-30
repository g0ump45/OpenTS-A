---
key: LeptonsPerSightIncrease
summary: Leptons of height that earn an object ten per cent more sight range.
see_also: ["system:map-visibility", Sight, VeteranSight]
when_omitted:
  kind: value
  value: "50"
---

The elevation of the object's own coordinate is divided by this value and the whole-number result is worth ten per cent each, added to the type's [`Sight=`](/keys/sight/) before the veteran multiplier is applied. One height level is 104 leptons, so at the default a unit standing one level up sees a fifth further and one four levels up eighty per cent further.

The bonus is recomputed on every look and again when an object is placed on the map. A rise in it makes that same look a full scan rather than an incremental one.

:::danger[Zero divides by zero]
The height is divided by this value with no guard against zero. `LeptonsPerSightIncrease=0` divides by zero on the next look any object takes.
:::

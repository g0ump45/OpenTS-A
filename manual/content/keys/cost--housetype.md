---
key: Cost
scope: housetype
label: Country price multiplier
see_also: ["system:difficulty"]
when_omitted:
  kind: value
  value: "1.0"
---

Every price a house of this country pays is [the object's own `Cost=`](/keys/cost/#scope-aircrafttype) multiplied by this value, so a figure above 1 pays more. The product is worked out once, when the house is [given its difficulty slot](/systems/difficulty/#how-the-figures-are-combined), and not per order.

A campaign game drops the country's contribution, so this value shapes skirmish and multiplayer games only; the [difficulty setting's own multiplier](/keys/cost/#scope-difficulty-settings) applies in both. Prices and build times are separate axes: this value changes what everything costs without changing how long it takes.

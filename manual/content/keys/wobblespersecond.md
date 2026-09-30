---
key: WobblesPerSecond
summary: How many complete up-and-down cycles a hovering jumpjet unit performs each second.
see_also: [WobbleDeviation, CruiseHeight]
when_omitted:
  kind: value
  value: ".25"
---

The wave that carries the drift is advanced by a full circle divided by fifteen frames over this figure, so the count really is cycles per second of real play: at the stock `.25` a jumpjet takes four seconds to rise, fall and come back. [`WobbleDeviation`](/keys/wobbledeviation/) sets how far it travels in that time.

The wave runs only while the unit is hovering or cruising, and it is reset to its start whenever the unit is climbing, descending or grounded — so every jumpjet begins its wobble from the same point rather than from wherever the wave happened to stand.

```ini title="rules.ini"
[JumpjetControls]
WobblesPerSecond=.15
```

A figure of `0` divides in floating point and leaves the wave frozen at its start, which stops the drift without disturbing anything else; a negative figure runs the same wave in reverse, so the unit dips before it rises.

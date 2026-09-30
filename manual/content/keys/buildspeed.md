---
key: BuildSpeed
summary: The multiplier that turns an object's cost into its base build time.
when_omitted:
  kind: value
  value: "1"
---

Base build time in game frames is the object's [`Cost`](/keys/cost/#scope-aircrafttype) multiplied by this value and by nine tenths of a frame per credit, so at the default an object costing 1000 takes one minute to build. Everything else that shapes production — the country and difficulty [`BuildTime`](/keys/buildtime/) multipliers, the [power](/systems/power/#production) divisor, the count of factories, and the [wall coefficient](/keys/wallbuildspeedcoefficient/) — is applied to that figure afterwards.

The value applies to every producible object type, so raising it lengthens every build in the game rather than any one category.

---
key: Engineer
scope: infantrytype
label: Engineer soldier
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: "no"
---

Setting this also forces [`Infiltrate=yes`](/keys/infiltrate/) on, in the same pass and after that key has been read, so a section that carries `Engineer=yes` cannot write `Infiltrate=no`. The forcing is not undone: a later rules layer that writes `Engineer=no` over the type clears the engineer behavior and leaves the infiltrate behavior standing, which produces a soldier that still takes the enter cursor, still walks into the structure, and does nothing when it arrives.

The flag drives its own [cursor block](/systems/capture/#an-engineer-over-a-structure), the restore-or-capture split at the structure, and the bridge repair branch. It also changes how the soldier travels and what its owner points it at: an engineer is given its target as a movement destination instead of closing to weapon range, may walk into an occupied cell while on guard, area guard or patrol, skips target scanning on plain guard, and is treated as a special case throughout [target selection](/systems/target-selection/#what-each-kind-of-object-considers).

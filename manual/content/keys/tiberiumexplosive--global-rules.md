---
key: TiberiumExplosive
scope: global-rules
label: Exploding harvesters
see_also: ["system:tiberium", "Power", "Storage"]
when_omitted:
  kind: value
  value: "no"
---

A unit destroyed while holding any Tiberium adds a second blast to its normal explosion: reaching one and a half cells out, sourced to the unit, applied through [`C4Warhead`](/keys/c4warhead/), and worth the sum across every compartment of the amount carried multiplied by that type's [`Power`](/keys/power/#scope-tiberium). A scenario running with the harvester-truce option set skips the blast.

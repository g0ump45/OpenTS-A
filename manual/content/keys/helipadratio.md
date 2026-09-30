---
key: HelipadRatio
summary: Parsed helipad share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", HelipadLimit, Helipad]
when_omitted:
  kind: value
  value: ".12"
---

Nothing weighs a computer base by proportion. A [`Helipad=yes`](/keys/helipad/) type earns its extra copies during [the pass that assembles the plan](/systems/ai-base-building/#building-the-plan), which is the only place the count is decided.

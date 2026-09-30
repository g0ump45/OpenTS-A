---
key: RefineryRatio
summary: Parsed refinery share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", RefineryLimit, BuildRefinery]
when_omitted:
  kind: value
  value: ".16"
---

Nothing weighs a computer base by proportion. How many refineries a plan holds is settled while [the plan is assembled](/systems/ai-base-building/#building-the-plan): one arrives through the ordinary candidate scan, and the extra copies that follow it are counted out by difficulty from [`BuildRefinery`](/keys/buildrefinery/).

---
key: RefineryLimit
summary: Parsed ceiling on refineries that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", RefineryRatio, BuildRefinery]
when_omitted:
  kind: value
  value: "4"
---

No routine counts the refineries a computer house owns against a maximum. The number that reaches its base comes from [the pass that assembles the plan](/systems/ai-base-building/#building-the-plan), and the money branch of the planner can add one more at the current build position whenever the house cannot earn.

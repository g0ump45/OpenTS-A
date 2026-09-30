---
key: HelipadLimit
summary: Parsed ceiling on helipads that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", HelipadRatio, Helipad]
when_omitted:
  kind: value
  value: "5"
---

No routine counts the helipads a computer house owns against a maximum. How many a plan holds is fixed as [the plan is assembled](/systems/ai-base-building/#building-the-plan), where a [`Helipad=yes`](/keys/helipad/) type is appended a random number of extra times.

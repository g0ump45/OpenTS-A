---
key: InfantryReserve
summary: Parsed cash threshold for infantry production that the engine never uses.
no_effect: true
see_also: ["system:ai-team-production", InfantryBaseMult]
when_omitted:
  kind: value
  value: "2000"
---

A computer house does not build infantry against its balance. Which soldier it orders next comes from [the demand its own teams leave unfilled](/systems/ai-team-production/#production-demand), and money enters that decision only as the test that a candidate's cost is within the credits the house can spend.

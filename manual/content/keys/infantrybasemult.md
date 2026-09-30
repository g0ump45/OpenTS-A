---
key: InfantryBaseMult
summary: Parsed multiplier on building count for infantry production that the engine never uses.
no_effect: true
see_also: ["system:ai-team-production", InfantryReserve]
when_omitted:
  kind: value
  value: "2"
---

Nothing measures a computer house's infantry against the size of its base. Which soldier it orders next comes from [the demand its own teams leave unfilled](/systems/ai-team-production/#production-demand), counted per InfantryType and offset by the recruitable soldiers it already owns.

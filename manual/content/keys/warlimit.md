---
key: WarLimit
summary: Parsed ceiling on war factories that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", WarRatio, BuildWeapons]
when_omitted:
  kind: value
  value: "2"
---

No routine counts the war factories a computer house owns against a maximum. Each ownable type appears in [the assembled plan](/systems/ai-base-building/#building-the-plan) as often as that pass appends it, and the finished node list is what the house builds.

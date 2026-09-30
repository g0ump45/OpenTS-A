---
key: TeslaLimit
summary: Parsed ceiling on Tesla coils that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", TeslaRatio]
when_omitted:
  kind: value
  value: "10"
---

No BuildingType is treated as a Tesla coil anywhere in the engine, so there is no count for a ceiling to bound. What a computer house puts up in a defensive slot is settled by [the defense planner](/systems/ai-base-building/#base-defenses).

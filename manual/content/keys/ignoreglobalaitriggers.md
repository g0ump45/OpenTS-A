---
key: IgnoreGlobalAITriggers
summary: Whether the scenario passes over every AI trigger that was not defined by the map itself.
see_also: ["system:ai-team-production"]
when_omitted:
  kind: value
  value: "no"
---

The triggers loaded from `AI.INI` and `AIFS.INI` remain registered and enabled; they are simply [rejected as candidates](/systems/ai-team-production/#which-triggers-are-eligible) for every house. A map that sets this and defines no AI triggers of its own therefore leaves its computer houses with nothing to spring.

---
key: MaximumBaseDefenseValue
summary: Caps each of the three defense values computed for a base defense BuildingType.
see_also: ["system:ai-base-building"]
when_omitted:
  kind: value
  value: "60"
---

The cap is applied to the anti-air, anti-armor and anti-infantry value separately as each is [computed from the type's primary weapon](/systems/ai-base-building/#base-defenses). Because those values also weight the random draw between defense candidates, a cap low enough to saturate several types flattens the differences between them and leaves cost as the deciding term.

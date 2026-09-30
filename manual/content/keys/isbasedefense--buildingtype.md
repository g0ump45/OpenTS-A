---
key: IsBaseDefense
scope: buildingtype
label: Base defense building
see_also: ["system:ai-base-building"]
when_omitted:
  kind: value
  value: "no"
---

Only a type carrying this flag has its anti-air, anti-armor and anti-infantry values [computed from its primary weapon](/systems/ai-base-building/#base-defenses), and a type whose three values stay at zero never enters a defense candidate list. Outside a campaign game, the node of such a building is retired to a fresh placeholder when the building is taken off the map, so the planner picks a new type and cell rather than rebuilding what was lost.

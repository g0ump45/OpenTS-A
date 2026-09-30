---
key: BuildAA
summary: Parsed anti-aircraft defense list for a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", AALimit, IsBaseDefense]
when_omitted:
  kind: value
  value: ""
---

Anti-aircraft defenses are not named to a computer house. A type qualifies for an anti-air node by having an anti-air value above zero, which every [`IsBaseDefense=yes`](/keys/isbasedefense/#scope-buildingtype) type is given from its primary weapon, projectile and warhead as the types load, and which [the defense planner](/systems/ai-base-building/#base-defenses) then reads.

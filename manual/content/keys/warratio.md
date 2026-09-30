---
key: WarRatio
summary: Parsed war factory share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", WarLimit, BuildWeapons]
when_omitted:
  kind: value
  value: ".1"
---

Nothing weighs a computer base by proportion. A war factory reaches the plan because [the first ownable `BuildWeapons` entry is moved to the second slot of the candidate array, behind the barracks](/systems/ai-base-building/#building-the-plan) and because other types name it as a prerequisite, never because a share of the base was reserved for it.

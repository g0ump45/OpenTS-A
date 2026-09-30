---
key: BarracksRatio
summary: Parsed barracks share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", BarracksLimit, BuildBarracks]
when_omitted:
  kind: value
  value: ".16"
---

Nothing weighs a computer base by proportion. A barracks reaches the plan because [the first ownable `BuildBarracks` entry is moved to the head of the candidate array](/systems/ai-base-building/#building-the-plan) and because other types name it as a prerequisite, never because a share of the base was reserved for it.

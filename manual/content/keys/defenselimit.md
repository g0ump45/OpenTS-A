---
key: DefenseLimit
summary: Parsed ceiling on defensive buildings that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", DefenseRatio, MaximumBaseDefenseValue]
when_omitted:
  kind: value
  value: "40"
---

No routine counts the defenses a computer house owns against a maximum. The number of defense placeholders in a plan follows from [the build cost accumulated as the plan is assembled](/systems/ai-base-building/#building-the-plan), and each placeholder is filled in later by [the defense planner](/systems/ai-base-building/#base-defenses) or deleted when it cannot be.

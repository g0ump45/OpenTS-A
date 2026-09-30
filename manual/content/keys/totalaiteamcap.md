---
key: TotalAITeamCap
summary: The number of live teams a house may hold before its AI triggers stop springing, one entry per difficulty.
see_also: ["system:ai-team-production", MaximumAIDefensiveTeams, MinimumAIDefensiveTeams]
when_omitted:
  kind: value
  value: ""
  note: The list stays empty and the difficulty slot is used to index it anyway, reading storage that was never allocated.
---

Entries run hardest game setting first, and a computer house indexes them with its own difficulty slot, which is the inverse of the setting the player chose. The count includes every team the house owns, teams the scenario placed among them. A house at or above the cap does not simply stop: if its defensive teams have also reached half its team count, rounded down, the pass [deletes the oldest of them](/systems/ai-team-production/#the-team-budget), and selection continues only if that deletion brings the count back under the cap.

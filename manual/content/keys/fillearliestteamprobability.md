---
key: FillEarliestTeamProbability
summary: The percent chance that the next vehicle, infantryman or aircraft chosen goes to the oldest waiting team, one entry per difficulty.
see_also: ["system:ai-team-production"]
when_omitted:
  kind: value
  value: ""
  note: The list stays empty and the difficulty slot is used to index it anyway, reading storage that was never allocated.
---

Entries run hardest game setting first, and a computer house indexes them with its own difficulty slot, which is the inverse of the setting the player chose. The draw is made once per [production choice](/systems/ai-team-production/#production-demand) in each of the three routines. Winning it selects the type wanted by the team that has waited longest; losing it selects uniformly from the candidate list, which is what spreads production across several teams at once.

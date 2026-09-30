---
key: RatioTeamUnits
summary: Parsed vehicle share that the engine never uses.
no_effect: true
see_also: [RatioTeamAircraft, RatioTeamInfantry, RatioAITriggerTeam, "system:ai-team-production"]
when_omitted:
  kind: value
  value: "75"
---

The name promises the share of a computer house's production effort that goes to the vehicles its teams ask for. The figure is stored on the house and can be rewritten while the scenario runs by the [Ratio of team units...](/mapping/actions/taction-set-team-unit-ratio/) trigger action, but nothing ever reads it back. Its two companions, [`RatioTeamAircraft`](/keys/ratioteamaircraft/) and [`RatioTeamInfantry`](/keys/ratioteaminfantry/), are equally inert; only [`RatioAITriggerTeam`](/keys/ratioaitriggerteam/), which shares the naming, reaches a decision. No gameplay path reads the share.

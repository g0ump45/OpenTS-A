---
key: RatioTeamInfantry
summary: Parsed infantry share that the engine never uses.
no_effect: true
see_also: [RatioTeamAircraft, RatioTeamUnits, RatioAITriggerTeam, "system:ai-team-production"]
when_omitted:
  kind: value
  value: "75"
---

The name promises the share of a computer house's production effort that goes to the infantry its teams ask for. The figure is stored on the house and can be rewritten while the scenario runs by the [Ratio of team infantry...](/mapping/actions/taction-set-team-infantry-ratio/) trigger action, but nothing ever reads it back. Its two companions, [`RatioTeamAircraft`](/keys/ratioteamaircraft/) and [`RatioTeamUnits`](/keys/ratioteamunits/), are equally inert; only [`RatioAITriggerTeam`](/keys/ratioaitriggerteam/), which shares the naming, reaches a decision. No gameplay path reads the share.

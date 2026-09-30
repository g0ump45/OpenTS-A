---
key: AttackInterval
summary: Parsed spacing between computer attacks that the engine never uses.
no_effect: true
see_also: ["system:ai-team-production", AttackDelay, TeamDelays]
when_omitted:
  kind: value
  value: "3"
---

Nothing paces a computer house's offensives on an interval of its own. Attacking forces reach the map as ordinary teams, drawn one suggestion at a time by [the AI trigger pass](/systems/ai-team-production/#when-the-pass-runs), whose countdown is [`TeamDelays`](/keys/teamdelays/).

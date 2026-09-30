---
key: AutocreateTime
summary: Parsed number that the engine never uses.
see_also: ["system:ai-team-production", TeamDelays]
no_effect: true
when_omitted:
  kind: value
  value: "5"
---

The interval a house actually raises teams on is [`TeamDelays`](/keys/teamdelays/), a frame count chosen by difficulty.

---
key: PlayerAutoCrush
summary: Parsed crushing permission that the engine never uses.
no_effect: true
see_also: ["Crush", "AutoCrush", "Crusher"]
when_omitted:
  kind: value
  value: "no"
---

The one test that reads it asks first whether the crushing vehicle belongs to a house a person is commanding, and the routine holding that test is only ever entered for a house under computer control. The question is settled before the setting is reached, so nothing a player commands is affected either way.

[`Crush`](/keys/crush/) covers what does decide whether a computer-controlled vehicle drives over a target instead of shooting it.

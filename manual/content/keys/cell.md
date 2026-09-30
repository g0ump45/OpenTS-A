---
key: Cell
summary: Parsed trap cell that nothing ever reads back.
no_effect: true
see_also: ["Coord", "Target", "Type", "Frame"]
when_omitted:
  kind: value
  value: "0,0"
---

The sync-bug settings are read only as the multiplayer menu is entered, and only while recording playback is armed. The two comma-separated numbers name a map cell to watch; cell `0,0`, which is also the value used when the setting is left out, counts as no cell at all and is rejected.

Any other pair stores a pointer to that cell, and nothing anywhere reads the pointer. No gameplay path acts on it.

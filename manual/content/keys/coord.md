---
key: Coord
summary: Parsed trap coordinate that is thrown away as soon as it is read.
no_effect: true
see_also: ["Cell", "Target", "Type", "Frame"]
when_omitted:
  kind: value
  value: "0"
  note: Parsed like any other value, and the trap coordinate keeps the no-coordinate value it was constructed with either way.
---

The sync-bug settings are read only as the multiplayer menu is entered, and only while recording playback is armed. The name promises the world coordinate of the object the hunt should stop on, written as three comma-separated numbers.

All three are pulled out of the value and then discarded without being stored anywhere, and the coordinate the hunt would have compared against keeps the no-coordinate value it was constructed with. No gameplay path reads the setting.

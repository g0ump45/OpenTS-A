---
key: Frame
summary: Parsed trap frame that reaches a routine with nothing in it.
no_effect: true
see_also: ["Type", "Target", "Cell", "Coord", "PrintCRC"]
when_omitted:
  kind: value
  value: "2147483647"
---

The sync-bug settings are read only as the multiplayer menu is entered, and only while recording playback is armed. The name promises the frame from which the engine starts hunting for the object the rest of them describe, so that a debugger can be pointed at it.

From that frame on the hunt is indeed called once per game frame, but its body is compiled out of the build, so it examines nothing and stores nothing. Nothing else reads the number, and reaching the frame changes nothing.

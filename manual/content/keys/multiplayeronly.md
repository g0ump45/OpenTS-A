---
key: MultiplayerOnly
summary: Parsed flag that restricts nothing.
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

The name promises a scenario that may be played only in a multiplayer game. The flag is stored from the map's `[Basic]` section and written back out by the map editor — as a number rather than a switch, which is why the shipped missions carry `MultiplayerOnly=0` — and nothing reads it back. Neither the campaign progression nor the lobby's map list consults it, so no gameplay path reads it.

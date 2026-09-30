---
key: Type
scope: multiplayer-settings
label: Sync-bug trap object kind
no_effect: true
see_also: ["Frame", "Target", "Cell", "Coord"]
when_omitted:
  kind: value
  value: "NONE"
---

The sync-bug settings are read only as the multiplayer menu is entered, and only while recording playback is armed. `AIRCRAFT`, `ANIM`, `BUILDING`, `BULLET`, `INFANTRY` and `UNIT` are recognized here without regard to letter case, and every other value, `NONE` included, narrows the search to nothing in particular.

The name promises the kind of object the hunt should look through, but the routine that would do the looking has an empty body. No gameplay path reads the choice.

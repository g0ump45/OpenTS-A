---
key: Target
summary: Parsed trap target that reaches a routine with nothing in it.
no_effect: true
see_also: ["Coord", "Cell", "Type", "Frame"]
when_omitted:
  kind: value
  value: "-1"
---

The sync-bug settings are read only as the multiplayer menu is entered, and only while recording playback is armed. The number is decoded into the target the hunt would compare each object against, and unlike the neighboring coordinate it really is stored.

It is then never compared with anything, because the routine that would do the comparing has an empty body. No gameplay path reads the target.

---
key: SellSound
summary: Sound played as a structure, a unit or a wall section is sold back.
see_also: [CrumbleSound, GenericClick, RefundPercent, Unsellable]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
SellSound=SELL1 ; a sound ID registered in SOUND.INI
```

Three sales play it.

A structure beginning its build-down plays it from its own position, so it fades with distance from the view, and only for a player-controlled house. A structure that undeploys into a vehicle is torn down without it; a construction yard, which undeploys but is not treated as a vehicle, still plays it.

A unit sold back at a repair bay plays it at full volume rather than from a place on the map, again only for a player-controlled house, alongside the spoken "unit sold" line.

A wall section sold back plays it at full volume, and only when the selling house is the local player's own. Wall removal has a silent form as well, and that is the default: a section cleared to make room for a structure being placed over it, and the walls of a defeated house being swept up, both take the silent form. The sale the player orders and the sell-off an AI runs over its own base take the loud one.

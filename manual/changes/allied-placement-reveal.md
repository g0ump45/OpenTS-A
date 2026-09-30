---
title: Reveal an ally's structure the moment it is placed
category: fix
release: 0.2.0
targets:
- type: system
  id: map-visibility
  effect: changed
- type: key
  id: AllyReveal
  effect: changed
credit: [ZivDero, Rampastring]
---

Outside a campaign, a structure an ally places now lifts the player's shroud around itself
as soon as it goes down, as it already did on the ally's own screen. Only an object of the
player's own house took a look when the player discovered it; now every discovered object
does, and the map keeps deciding whose shroud that look lifts, so a stranger's object still
reveals nothing. A campaign keeps the look to the player's own objects.

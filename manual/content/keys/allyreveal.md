---
key: AllyReveal
summary: Whether an ally's objects reveal terrain for the local player.
see_also: ["system:map-visibility"]
when_omitted:
  kind: value
  value: "yes"
---

A look is performed for the house that owns the object, and only the local player's own house has a shroud to lift. At `yes` a look by a house allied to the local player is redirected to the local player instead, which is what makes an ally's sight worth anything on screen; at `no` it reveals nothing. Outside a campaign every object also looks the moment the local player discovers it, which at `yes` is what lets a structure an ally places lift the shroud around itself as soon as it goes down.

The flag is read on two further occasions. Forming an alliance with the local player makes every object of the new ally take an ordinary look at once, so a [passive house](/keys/multiplaypassive/) that allies outside a campaign reveals nothing. And the sweeps that re-reveal the map after a [shroud or fog pass](/systems/map-visibility/#losing-ground-again) take in an ally's structures alongside the player's own objects — where an ally's structure is the one thing that maps cells rather than merely reporting them watched.

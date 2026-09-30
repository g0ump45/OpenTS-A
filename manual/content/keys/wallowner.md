---
key: WallOwner
summary: Whether the country's buildings can claim ownership of nearby walls placed with the map.
see_also: ["system:walls-and-gates"]
when_omitted:
  kind: value
  value: "yes"
---

Walls that arrive with the map carry no owner. The pass that runs after the map is loaded hands each wall cell to the house whose nearest active, placed building belongs to a country with this flag; a map with no such building anywhere leaves its walls unowned, and an unowned wall cannot be sold and is not an anchor for the [automatic gap fill](/systems/walls-and-gates/#filling-the-gap-to-the-next-wall). Walls the player builds are stamped with their house directly and never consult this.

:::caution[The value is overwritten outside campaign]
Skirmish, multiplayer and random-map setup rewrite the flag before play begins, on every country that has a house in the game: a [`MultiplayPassive=yes`](/keys/multiplaypassive/) country is forced to `no` and every other country to `yes`. An authored `WallOwner=` therefore only holds in a campaign game.
:::

---
key: MultiplayPassive
summary: Takes the country's houses out of the contest, so they are neither fought nor counted.
see_also: [Multiplay, WallOwner, Allies]
when_omitted:
  kind: value
  value: "no"
---

```ini title="rules.ini"
[Neutral]
MultiplayPassive=true
```

A passive country's houses run no computer AI at all, in any kind of game. Neither the expert-system pass that chooses attacks and teams nor the production passes that queue buildings, units, infantry and aircraft is entered for one, so such a house only ever owns what the map gave it.

Everything else the flag does is confined to skirmish and multiplayer games, where a passive house is treated as scenery rather than as an opponent.

- It is exempt from the defeat check that removes a player who has run out of objects, and its defeat is not announced.
- It is not counted among the players still alive, nor in the test for whether everyone left is allied — except in a skirmish game, where that second exclusion is dropped.
- A computer house never picks it as an enemy, and it never picks one of its own.
- Its objects are rejected outright by automatic target scans, and they never open a crate they drive over.
- Its objects do not reveal the map, and its buildings are never marked for automatic repair.
- It is skipped by the score screen and by the starting-unit generator.

An [observer's](/systems/observers/) house is left out of the same counts, lists and scores without being passive: it plays a country chosen at random and simply starts defeated.

Setup also rewrites two things on its behalf. [`WallOwner`](/keys/wallowner/) is forced off on every passive country and on for every other one, and every house in the game is allied to the house of the country named `Special`.

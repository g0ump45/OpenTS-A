---
key: GameClosed
summary: Sound played in the network game list when a listed game stops accepting players.
see_also: [GameForming, PlayerJoined, PlayerLeft, SystemError]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
GameClosed=GAMESHUT ; a sound ID registered in SOUND.INI
```

The sound belongs to the network game list a player sits in before joining a LAN match, and it is played without a position. It marks one announcement: a game already on the list going from open to closed, which the host reports in the answers it broadcasts about itself. The chat panel prints a matching line beside it.

The announcement is made only while the player has not yet been confirmed into a game, so a game closing behind an already-joined player is silent. A game that drops off the list entirely, rather than reporting itself closed, is also silent.

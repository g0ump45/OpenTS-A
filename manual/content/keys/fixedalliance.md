---
key: FixedAlliance
summary: Parsed flag that locks nothing.
no_effect: true
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

Two conditions have to meet for this flag to matter, and they exclude each other. The map's `[SpecialFlags]` block is parsed only in a single-player mission or with the map debugger active; the one routine that consults the locked-alliance state — the command that offers to ally with the owner of a selected object — refuses to run in a single-player mission. Every game type that could reach the command also replaces the scenario's flags wholesale with the lobby's set as soon as the map has been read, so nothing the map wrote survives to be tested.

Locked alliances come from the network setup instead, which sets the state directly when the alliances were dictated from outside the game and clears it when the players are free to negotiate. Whatever the map says here reaches no gameplay path at all.

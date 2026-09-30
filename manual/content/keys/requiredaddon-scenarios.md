---
key: RequiredAddOn
summary: The expansion whose rules, art and speech the mission is played under.
see_also: [SpeechSide, Name]
when_omitted:
  kind: context-dependent
  note: 0, the base game, in a campaign mission; in a multiplayer or skirmish game the expansion the session was started under, which the map's value then replaces if it carries one.
---

```ini title="map file"
[Basic]
RequiredAddOn=1
```

`0` names the base game and `1` names Firestorm. A campaign mission is checked against the number before anything else is loaded: every expansion is switched off, the number is recorded as the game's requirement, and the load is abandoned when that expansion is not installed. The expansion is then switched on, so its rules, art and speech apply for the remainder of the load. Because the check runs first, a number naming no installed expansion — anything above `1` on a stock installation — refuses the mission rather than falling back on the base game.

The stored number also selects the file the mission's title and briefing text are read from: `MISSION.INI` at `0`, and `MISSION1.INI` at `1`. The objectives screen consults the same number for the same purpose while the mission is being played.

Outside a campaign the expansion in force comes from the lobby and this key switches nothing. The value is still stored, so a multiplayer map that carries a number changes only which mission file is consulted for its text.

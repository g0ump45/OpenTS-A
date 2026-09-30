---
key: StartingDropships
summary: How many dropships the player fills before a campaign mission begins.
see_also: [AllowableUnits, AllowableUnitMaximums]
when_omitted:
  kind: value
  value: "0"
---

```ini title="map file"
[Basic]
StartingDropships=2
```

Any figure above zero opens the loadout screen after the briefing and before the action movie, with five slots to a dropship. The units chosen there fill the player house's three dropship slots in order. A reinforcement whose task force names `DSHP` and nothing else then arrives carrying a dropship's load, so the mission's own triggers decide when each one lands. The slot is checked and counted on the player's house but read and advanced on the reinforcement's, and only the player's house is ever given a loadout. A dropship reinforcement sent for any other house therefore draws its cargo from three slots nothing ever filled: the loadout begins with its entry count at zero but its five unit pointers never set, and the reinforcement takes as many of them as the player is currently carrying, handing each to the game as an object type without checking it. The same mismatch suppresses the delivery outright while the player's own current loadout is empty, so it goes wrong only once the player has filled theirs. Zero skips the screen entirely, which is what nearly every mission does.

[`AllowableUnits`](/keys/allowableunits/) decides what the screen offers.

:::danger[Asking for more than three reads past the end of fixed tables]
The screen picks its backdrop and its slot positions out of tables with three entries each, and indexes them with the figure given, minus one, without checking the range. A figure of four or more reads past the end of both tables and hands the result to the file loader and the button layout, and the chosen units are then stored into three per-house slots that a fourth dropship also overruns.
:::

---
key: AutoSaveInterval
summary: How many frames pass between one automatic save and the next in a game started from the menu, or zero for none.
see_also: [GameSpeed]
when_omitted:
  kind: value
  value: "10800"
---

When the frames have run out, the game posts `Auto-saving...` to the message list, writes the save at the next frame boundary, and replaces that line with the outcome. [Save games](/formats/save-games/#automatic-saves) owns the names the saves take, how they rotate, and what starts the count over. Frames are the game's own clock, so a faster [`GameSpeed`](/keys/gamespeed/) saves more often by the wall clock. A game against other machines arranged from the menu never saves automatically, whatever the figure, because every machine would have to carry the same one.

A [launch file](/formats/spawn-ini/#automatic-saves) that names an interval of its own takes this one's place for the game it starts, whether that turns the saves on or off.

The figure is read from `sun.ini` when the game starts and written back with the other options; no dialog offers it.

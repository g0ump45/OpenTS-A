---
key: GameSpeed
summary: The pace the game is held to, counted in sixtieths of a second between frames.
see_also: [ScrollRate, DetailLevel]
when_omitted:
  kind: value
  value: "3"
---

A frame is not begun until the delay has run out, so a larger figure gives a slower game: `0` runs as fast as the machine manages and `3` holds the game to twenty frames a second at most. The delay governs a single player mission, a skirmish, and a network game still using the older command protocol; a network game on the current protocol turns the figure into a frame rate instead — 60 at `0`, 45 at `1`, and sixty divided by the figure above that — and runs at whichever is lower, that or the rate the machines can sustain.

The same figure rescales the delays that have to keep their real-world timing whatever the frame rate is — building animations, infantry sequences and the pauses between EVA reminders — so that lowering it speeds the game up without speeding those up in proportion.

The in-game game controls dialog offers seven positions and writes the choice back to `sun.ini`, and so does the options screen. A multiplayer lobby overwrites the figure with the speed the session settled on, and the in-game speed control issues an order that changes it for every player at once.

:::danger[A negative figure divides by zero and a large one reads past a table]
Nothing narrows the figure on the way in. `-1` makes the divisor zero and the game stops on a division fault as soon as a delay of five frames or more is rescaled, which a building animation or an EVA reminder does within moments of a scenario starting. A figure of `8` or more reads past the end of the rescaling table used for the delays shorter than that.
:::

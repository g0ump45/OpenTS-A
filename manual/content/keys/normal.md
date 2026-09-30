---
key: Normal
summary: Offers the score to the playlist the game picks from automatically.
see_also: [Repeat, Scenario, Side]
when_omitted:
  kind: value
  value: "yes"
---

```ini title="theme.ini"
[INTRO]
Name=Intro
Length=3.27
Normal=no
Repeat=yes
```

A score that is not normal is skipped by the routine that decides what plays next, and it is left out of the track list on the sound options screen, so a player cannot pick it there either. It can still be started outright by name, which is how the menu, map selection and score-screen music reaches the player without ever appearing on the playlist.

The same routine also applies [`Scenario`](/keys/scenario/#scope-themes) and [`Side`](/keys/side/#scope-themes), and drops any score whose audio file is missing from the mixfiles.

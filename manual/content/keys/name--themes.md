---
key: Name
scope: themes
label: Score display name
see_also: [Length, Normal]
when_omitted:
  kind: value
  value: ""
  note: An empty name, which leaves the score's row in the track list blank.
---

The value is displayed literally rather than being looked up as a translatable label, and it is held in a 64-byte field, so it is cut off after 63 characters. A player sees it in the sound options track list, where each score the playlist would accept is listed by this name with its [`Length`](/keys/length/) beside it.

```ini title="theme.ini"
[DUSKHOUR]
Name=Dusk Hour
Length=4.11
Scenario=1
Side=GDI
```

The section name is the audio file's own name and is what the rest of the engine identifies a score by, but this name is a lookup key as well. Turning a name into a score matches section names first, without regard to letter case, and then falls back to a case-sensitive substring search over the display names. Every request for a score by name runs through that routine — the menu, map selection and score-screen music, a scenario's [`Theme=`](/keys/theme/), and the reader that builds the score list itself — so a display name containing another score's section name answers to that section name, and a `[Themes]` entry whose ID appears inside an existing display name amends that score instead of adding one of its own.

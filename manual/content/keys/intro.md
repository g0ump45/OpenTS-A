---
key: Intro
summary: The movie played first when a campaign mission is started with its briefing.
see_also: [Brief, Action, Win, Lose, PostScore, PreMapSelect]
when_omitted:
  kind: value
  value: "<none>"
---

```ini title="map file"
[Basic]
Intro=INTRO
Brief=GDI_M02
```

The value names an entry of the art file's `[Movies]` list rather than a file; the engine appends `.VQA` to the registered name when it goes looking for the film. `<none>`, an empty value, and any name the list does not carry all leave the setting as it was, which is what omitting the key does too.

The movie runs once the scenario has been read and just before [`Brief`](/keys/brief/), and only when the mission was started fresh. A mission replayed after a loss or restarted from the menu passes over both. Movies are never played outside a campaign, and a registered name whose `.VQA` file is missing, or whose picture is both narrower than 320 and shorter than 200, is skipped in silence.

:::danger[A long registered movie name overruns a fixed buffer]
Every movie assignment is resolved by one shared routine, which copies the registered name and the `.VQA` suffix into a 20-byte buffer without checking the length. A `[Movies]` entry longer than fifteen characters writes past the end of that buffer, over whatever the linker placed after it. The names the game ships are eight characters, so only a mod that registers longer ones can reach this.
:::

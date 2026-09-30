---
key: PostScore
summary: The movie played after the score screen of a won campaign mission.
see_also: [PreMapSelect, SkipScore, Win, Intro]
when_omitted:
  kind: value
  value: "<none>"
---

```ini title="map file"
[Basic]
PostScore=GDI_M09B
PreMapSelect=GDI_M11
```

The movie follows the score screen and precedes [`PreMapSelect`](/keys/premapselect/). It plays whether or not the score screen itself was shown, so a mission that sets [`SkipScore`](/keys/skipscore/) still gets it, and a recorded game being played back gets neither.

[`Intro`](/keys/intro/) covers how a movie name is resolved and what happens to one that cannot be found.

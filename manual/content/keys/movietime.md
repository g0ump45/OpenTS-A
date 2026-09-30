---
key: MovieTime
summary: Length, in minutes, intended for a debug screen capture sequence.
no_effect: true
when_omitted:
  kind: value
  value: ".25"
---

```ini title="rules.ini"
[AudioVisual]
MovieTime=.25
```

The value would size the buffer of off-screen surfaces a screen-capture aid allocates, at fifteen frames a second — the default is 225 frames, a quarter of a minute. Nothing calls that routine. The flag it waits on is only settable by a debug key that a release build does not compile, and the routine itself is reached from nowhere in any build, so no value of this setting has any effect.

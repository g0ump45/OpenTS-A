---
key: Rate
scope: animtype
label: Playback rate
when_omitted:
  kind: unchanged
  note: The read treats -1 as absent, keeping whatever frame delay the type already stores.
---

The value is the animation's playback rate in frames of the animation per minute of game time: the engine stores `900` divided by it, in whole numbers, as the wait between one animation frame and the next. `Rate=900` advances every game frame, `Rate=450` every second one, and a value of `0` or below stores no wait at all.

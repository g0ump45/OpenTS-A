---
key: DeathFrameRate
summary: The number of game frames each frame of a vehicle's wreck animation is held for.
see_also: ["DeathFrames", "MaxDeathCounter", "StartDeathFrame"]
when_omitted:
  kind: value
  value: "1"
---
The frame of the run to draw is the wreck's death counter divided by this figure, so the run takes `DeathFrames × DeathFrameRate` game frames to play through — 15 game frames to the second. Once it has played through, the last frame is held until the counter passes [`MaxDeathCounter`](/keys/maxdeathcounter/) and the wreck explodes, so a run that finishes early leaves the wreck sitting on its final frame for the rest of its time. The count is kept in a single signed byte, so `256` stores as zero and any figure above `127` stores as a negative number.

A figure below `1` is raised to `1` as the section is read, so `DeathFrameRate=0` and negative figures all hold each frame for one game frame.

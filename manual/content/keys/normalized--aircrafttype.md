---
key: Normalized
scope: aircrafttype
label: Building animation rate
when_omitted:
  kind: value
  value: "no"
---

Only a building reads the flag. The first animation state a building takes, and any state set while the scenario is being set up, has the frame delay that state was configured with is rescaled against the game speed setting rather than used as written, so the animation keeps roughly the same rate on the clock however fast or slow the match is running. The exemption applies only where the flag is read. Two other paths — the queued change of animation state, and the restart at the end of a loop — rescale the construction and idle states unconditionally, whatever this flag says.

An aircraft, infantry type, or vehicle stores the flag and never consults it.

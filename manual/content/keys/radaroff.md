---
key: RadarOff
summary: Sound played as the radar pane begins closing.
see_also: ["system:map-visibility", RadarOn]
when_omitted:
  kind: value
  value: "<none>"
---

The sound plays without a position, at the moment the pane is put into its closing state, which the house losing its radar and the mode cycle dropping a player-names display back to a radarless pane are two occasions of among several. Unlike [`RadarOn`](/keys/radaron/), the branch carries no guard against the pane already being closed or closing, so the sound can play again over a pane that is already shut. [Power output and drain](/systems/power/#radar) covers what takes the radar away.

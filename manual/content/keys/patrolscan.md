---
key: PatrolScan
summary: How often a patrolling team looks around for something to attack.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: ".016"
---

The value is given in minutes and turned into a whole number of frames, so the default is 14 frames at 900 frames to the game minute. It is consulted by one thing only: the [Patrol to waypoint...](/mapping/missions/tmission-patrol/) team mission, which on each qualifying frame asks its leader for the greatest threat within the leader's own [`GuardRange`](/keys/guardrange/), falling back on its weapon range only where that setting is zero, and turns the patrol into an attack when it finds one. Finding nothing puts the team back on course for its waypoint.

The interval is measured against the game frame rather than against each team's own clock, so every patrolling team in the scenario scans on the same frames.

:::danger[An interval shorter than one frame divides by zero]
The frame counter is divided by the interval without any check that the interval is at least one. `PatrolScan=0`, and any value smaller in magnitude than `1/900`, which is about `0.0011`, leaves it at zero once multiplied out and truncated, and the first team to reach a Patrol mission divides by zero.
:::

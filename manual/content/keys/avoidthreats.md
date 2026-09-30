---
key: AvoidThreats
summary: Fixes every member's threat avoidance at `1` while it is on the team.
see_also: ["system:base-attacked", ThreatAvoidanceCoefficient]
when_omitted:
  kind: value
  value: "no"
---

Each time a member asks how much weight to give [the region threat figures](/systems/base-attacked/#what-reads-the-map), the answer is `1` while its team's TeamType is marked this way, whatever [`ThreatAvoidanceCoefficient`](/keys/threatavoidancecoefficient/) its own type carries. The question is asked afresh on every route, so a member reverts to its type's own coefficient the moment it leaves the team.

At `1` the pathfinder refuses a diagonal shortcut through any region carrying a threat figure of `1` or more, and counts every such cell of a straight-line leg as threatened.

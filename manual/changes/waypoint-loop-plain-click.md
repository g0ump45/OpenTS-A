---
title: Close a waypoint loop with a plain click
category: feature
release: 0.2.0
targets:
- type: command
  id: WaypointMode
  effect: changed
- type: system
  id: waypoint-paths
  effect: added
credit: [ZivDero, dkeeton]
---

In waypoint mode a plain click on an earlier waypoint of the path being plotted now closes the loop there; Shift is no longer needed. Shift with the click picks the waypoint up to move it instead, which a plain click did before. The last waypoint of the path and the waypoints of other paths still pick up on a plain click.

dkeeton is credited for the ts-patches change this follows.

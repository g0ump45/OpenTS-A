---
title: Draw start positions from placed waypoints before open ground
category: fix
release: 0.2.0
targets:
- type: system
  id: starting-forces
  effect: changed
- type: key
  id: Official
  scope: scenarios-2
  effect: changed
credit:
- ZivDero
---

A house now starts on open ground only when the map's eligible waypoints `0` through `7` have all been taken. An unofficial map was padded to eight positions with random open ground before the first house drew, so a house could start away from every placed waypoint while one stood free. Which waypoints `Official` makes eligible is unchanged.

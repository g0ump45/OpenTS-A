---
title: Ignore allied sensors around cloaked structures
category: fix
release: 0.1.0
targets:
- type: system
  id: cloaking
  effect: changed
- type: key
  id: Sensors
  effect: changed
credit: [ZivDero, Rampastring]
---

A structure now keeps or begins its cloak while a nearby detector considers the structure allied. Both structure checks use the detector owner's alliance list, matching the existing detector check for moving vehicles, infantry and aircraft.

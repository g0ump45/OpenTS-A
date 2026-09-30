---
title: Keep limbo objects out of radar tracking
category: fix
release: 0.1.0
targets:
- type: system
  id: map-visibility
  effect: changed
credit: [ZivDero, AlexB]
---

An object in limbo can no longer be added back to the radar tracking table. Radar-position updates reject it before discovery or detection work, and repeated limbo cleanup removes an existing stale entry before the object is destroyed.

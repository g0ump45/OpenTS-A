---
title: Cancel placement and input modes when input locks
category: fix
release: 0.1.0
targets:
- type: action
  id: TACTION_LOCK_INPUT
  effect: changed
credit: [ZivDero, tomsons26]
---

Taking control away from the player now cancels a structure waiting to be placed and drops
the repair, sell, power and waypoint modes before the lock takes hold. Locking input used
to leave all of them standing, so a scripted sequence that began while the player held a
building on the cursor gave the mission back with the placement grid or a special cursor
still active.

---
title: Fix attack-move when no enemy is found
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Attack-move no longer dereferences an empty threat scan or a cleared combat target. Patrol units continue toward their destination when no enemy is found and retain the existing engagement and return transitions. The Android long-press gesture is unchanged. Saved-game and network layouts are unchanged.

Infantry firing also skips the incoming-fire warning when its combat target or weapon is absent after firing. No save or network fields change.

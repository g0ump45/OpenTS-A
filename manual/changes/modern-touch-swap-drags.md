---
title: Swap Modern Touch pan and selection drags
category: feature
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Modern Touch adds an optional Swap pan / box drag setting, off by default.
When enabled, a single hold-and-drag pans the battlefield and a second-tap
drag selects a box. Stationary long-press attack-move, tap orders, same-type
selection, pinch zoom and right-click gestures retain their existing actions.
The version 2 settings file appends an optional swap flag. Older settings
retain their existing adjustments and default to the original drag layout;
older builds ignore the new flag and discard it when saving. Game saves and
network layouts are unchanged.

---
title: Fix Android touch orders and background audio
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Modern Touch removes the selection-box and double-tap enable switches. Both gestures remain enabled, including when loading older disabled settings. New settings and Reset Controls enable swapped pan/box dragging; existing saved swap choices remain intact.

Battlefield taps wait for the double-tap interval so a second-tap drag can cancel the first order. The root options panel leaves equal space above and below its buttons. Audio pauses when the app loses focus or enters the background. Game saves and network formats are unchanged.

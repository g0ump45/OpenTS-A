---
title: Match the Android minimap to the visible battlefield
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- g0ump45
---

The minimap viewport box follows the camera position, visible battlefield crop, and pinch zoom. Its edges scale directly and stay within the minimap border. Mission-triggered objective pings redraw on the always-visible Android minimap.

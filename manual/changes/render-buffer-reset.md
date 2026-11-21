---
title: Clear single-entry depth and alpha runs
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Depth and alpha resets now clear aligned single-entry runs instead of leaving
stale values. Buffer layouts and pan offsets are unchanged. See
[Android rendering checks](../../docs/ANDROID-RENDERING.md) for validation limits.

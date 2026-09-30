---
title: Show Android import only when game data is missing
category: fix
release: 0.2.0
targets:
- type: command
  id: Options
  effect: changed
credit:
- g0ump45
---

The Android game selector no longer offers Import Game Files. Startup still opens the importer automatically when game data is missing; see [Android game-file import](../../docs/ANDROID-GAME-FILES.md).

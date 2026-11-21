---
title: Fix Android import file precedence
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Android folder and ZIP import recognises client MIX folders and gives root files priority over main INI, MIX and Movies files, then nested copies. Equal-priority conflicts still stop import. See [Android game-file import](../../docs/ANDROID-GAME-FILES.md).

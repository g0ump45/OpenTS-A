---
title: Correct Android update verification and Spanish objectives
category: fix
release: 0.2.0
targets:
- type: system
  id: android-touch-controls
  effect: changed
credit:
- GEARS0FUMP45
---

Android updates handle missing current signer details without dereferencing a
null value; certificate matching remains required. Spanish fallbacks cover the
original base-game and Firestorm top-left mission messages, including split
objectives. Existing language packs need no download. See
[APK updates](../../docs/ANDROID-UPDATES.md) and
[game files](../../docs/ANDROID-GAME-FILES.md).

---
title: Honor the crates option after pickup
category: fix
release: 0.1.0
targets:
- type: system
  id: crates
  effect: changed
- type: key
  id: Crates
  effect: changed
credit: [ZivDero, Rampastring]
---

Collecting a crate outside a campaign now places a replacement only when both the multiplayer rules setting and the match's Crates option are enabled. A crate dropped by a destroyed vehicle therefore cannot seed random replacement crates while the match option is disabled.

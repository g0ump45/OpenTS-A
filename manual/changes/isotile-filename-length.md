---
title: Keep the whole file name on an isometric tile type
category: fix
release: 0.2.0
targets:
- type: key
  id: FileName
  effect: changed
credit: [ZivDero]
---

A tile set may now name its artwork with a stem of any length. A stem of eight characters, or seven on a set with lettered alternates, used to lose its artwork the first time the theater trimmed it out of memory, and drew nothing for the rest of the game.

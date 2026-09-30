---
title: Resume music rotation after scenario themes
category: fix
release: 0.1.0
targets:
- type: key
  id: Theme
  effect: changed
credit: [ZivDero, AlexB, Rampastring]
---

A scenario with no action movie now queues its configured `Theme` instead of starting it outside the score queue. After that score finishes, the score system selects another allowed track rather than ending the music rotation.

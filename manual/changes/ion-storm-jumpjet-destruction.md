---
title: Stop jumpjet flight processing after ion-storm destruction
category: fix
release: 0.1.0
targets:
- type: system
  id: ion-storms
  effect: changed
credit:
- ZivDero
- AlexB
---

An airborne jumpjet now ends locomotor processing as soon as ion-storm damage destroys it, puts it in limbo, or takes it out of active play. The destroyed infantryman no longer continues through a flight-state step, shroud work, or display-layer submission during that frame.

---
title: Recount superweapons safely while a scenario is cleared
category: fix
release: 0.1.0
targets:
- type: system
  id: superweapons
  effect: changed
credit: [ZivDero, Rampastring]
---

Clearing a scenario now lets each house finish updating its superweapons after the local player has been removed. Structures are deleted after that player pointer is cleared, and their removal can suspend or restore a powered superweapon. The availability update still runs, but targeting-mode and sidebar work is skipped until there is a local player again.

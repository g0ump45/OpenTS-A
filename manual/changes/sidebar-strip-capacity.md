---
title: Raise the sidebar strip capacity and hold its entries inside it
category: fix
release: 0.1.0
targets:
- type: system
  id: sidebar
  effect: changed
credit: [ZivDero]
---

A sidebar strip now holds 225 entries rather than 75, and it stops taking them at that
figure. The right-hand strip carries every vehicle, infantry, aircraft and superweapon a
house may build at the same time, so a rules set offering many buildable types filled it. The
capacity test then admitted one entry more than the strip has room for, which landed one
place beyond the array holding them and left the strip reporting a length it could not hold.

A cameo on a full strip answers its tooltip again. The tooltip was refused for every entry on
a strip that had reached its capacity, whichever entry the pointer rested on.

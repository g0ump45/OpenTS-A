---
title: Read every Tiberium type's damage from the rules
category: fix
release: 0.1.0
targets:
- type: key
  id: Power
  scope: tiberium
  effect: changed
credit: [ZivDero, AlexB, Rampastring]
---

A Tiberium section named `Vinifera` now keeps the damage its section states. The value was
overwritten with `17` once the section had been read, whatever the rules said, so that one
type could not be tuned at all. The Tiberium the game ships states `Power=20`, which is the
figure it now carries; a section that states nothing falls to the same `0` as every other
Tiberium type.

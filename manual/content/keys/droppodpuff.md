---
key: DropPodPuff
summary: Parsed animation reference that drop-pod logic never uses.
no_effect: true
see_also: [DropPod, DropPodWeapon, "system:drop-pods"]
when_omitted:
  kind: value
  value: none
---

The engine reads this `AnimType` reference from `[AudioVisual]`, but no runtime code creates the referenced animation.

Descending pods instead create the hard-coded `SMOKEY` animation every six frames, and only while [`DropPodWeapon`](/keys/droppodweapon/) is configured.

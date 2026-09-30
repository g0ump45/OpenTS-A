---
key: TreeFlammability
summary: Chance a burning terrain object sets fire to each unburnt terrain object beside it.
when_omitted:
  kind: value
  value: ".1"
---

The figure is a fraction from 0 to 1. A burning terrain object offers the fire around on roughly one frame in a hundred; on a frame it does, each of the eight neighboring cells holding a terrain object that is not already alight is drawn against separately, so a tree hemmed in on every side gets eight independent chances at once.

Winning the draw is not enough to catch. The neighbor must also not already be crumbling, its type must carry [`Armor=wood`](/keys/armor/#scope-aircrafttype) — which is what a TerrainType has unless its section sets something else — and it must not declare [`SpawnsTiberium=yes`](/keys/spawnstiberium/), so a blossom tree never burns. Those three conditions are the same ones a [`Sparky=yes`](/keys/sparky/) warhead has to clear when it starts the first fire.

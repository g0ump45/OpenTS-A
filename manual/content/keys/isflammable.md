---
key: IsFlammable
summary: Parsed terrain flag that the engine never uses.
no_effect: true
see_also: [TreeFlammability, SpawnsTiberium]
when_omitted:
  kind: value
  value: "no"
---

The name promises that the terrain object burns. No gameplay path reads the flag.

Terrain catches fire regardless of it. [`TreeFlammability`](/keys/treeflammability/) covers what actually decides whether a terrain object takes light: the type's armor and whether it spawns Tiberium stand in for the per-type flag this key's name promises.

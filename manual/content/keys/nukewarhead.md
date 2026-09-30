---
key: NukeWarhead
summary: Parsed WarheadType that the engine never uses.
no_effect: true
see_also: [AtomDamage, NukeProjectile, NukeDown, "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

The name promises the warhead a nuclear missile detonates with. A missile silo instead does its damage the way every other shot does, through the warhead on the firing superweapon's own weapon.

One path does read the value: the wide-area blast that [`AtomDamage`](/keys/atomdamage/) describes carries this warhead. That blast sits behind a test of whether the explosion animation was allocated at all, which the allocator never fails, so no gameplay path reads it.

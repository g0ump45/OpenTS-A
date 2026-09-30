---
key: Strength
scope: animtype
label: Maximum strength
no_effect: true
see_also: [Crushable, Damage]
when_omitted:
  kind: value
  value: "0"
---

The figure is stored as the type's maximum strength, which the engine consults when something takes damage, when a health ratio is worked out, and when a health ratio is written back. An animation reaches none of them. The blast sweep gathers its victims from a cell's occupier list, which an animation is never entered into, and from the aircraft, jumpjet-infantry and jellyfish rosters, which it never joins. It is on the logic list, which a heal crate walks without filtering by type, but that crate restores only what belongs to the house that opened it, and an animation answers to no house. Nothing creates an animation with a strength drawn from its type either. No gameplay path reads the figure.

The damage an animation deals to what is underneath it is [`Damage`](/keys/damage/#scope-animtype), which is unrelated to this.

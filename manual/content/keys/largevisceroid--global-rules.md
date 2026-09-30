---
key: LargeVisceroid
scope: global-rules
label: Merged visceroid type
see_also: ["SmallVisceroid"]
when_omitted:
  kind: value
  value: none
---

The named UnitType is what a small visceroid turns into when another merges into it. The creature that was standing still keeps its position, its house and its identity on the map, and is simply given this type and that type's full strength; the one that drove onto it deletes itself. [`SmallVisceroid=yes`](/keys/smallvisceroid/#scope-unittype) covers the approach that leads to it.

Nothing checks that the named type carries [`LargeVisceroid=yes`](/keys/largevisceroid/#scope-unittype) itself, so the two settings can name different things: a merge produces whatever is named here, and that result behaves as a large visceroid only if its own section says so.

A name that matches no declared UnitType does not resolve to no type; a UnitType of that name is brought into existence instead, configured by a section of the same name if the rules go on to supply one and left blank if they do not. The literals `none` and `<none>` are the exception: those do resolve to no type.

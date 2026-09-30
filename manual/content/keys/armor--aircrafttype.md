---
key: Armor
scope: aircrafttype
label: Armor class
see_also: [Verses, Wood, Immune]
when_omitted:
  kind: context-dependent
  note: Most object types start at none. A TerrainType starts at wood.
---

The class names the entry of the firing warhead's [`Verses`](/keys/verses/) list that the damage is multiplied by. Several steps reach the figure before that multiply and two more after it, and [Warheads and damage](/systems/warheads/) sets the whole order out. By the time the list is consulted, a prone soldier's own reduction has been applied, and a unit, structure, aircraft or infantryman has had its house's [difficulty and country divisors](/systems/difficulty/#how-the-figures-are-combined) and its veteran armor bonus taken out of the figure. After it come the falloff for distance from the point of impact, and then the warhead's floor and ceiling.

An OverlayType is the exception. A wall or a Tiberium patch is not an object and never reaches the step that consults a warhead's list, so its class is never a column there; every path that reads an overlay's class instead compares it against `wood` and nothing else, which is the other half of [`Wood=yes`](/keys/wood/) on a warhead. A TerrainType is read both ways — as a column when the object takes damage, and as a `wood` test by [the rules that set it alight](/keys/treefire/).

[`Tiberium=yes`](/keys/tiberium/#scope-overlaytype) rewrites an overlay's class to `wood` once that overlay's section has been read, so an `Armor=` written into such a section is discarded.

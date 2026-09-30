---
key: DropPodInfantryMaximum
summary: Upper bound for the number of infantry requested by the Drop Pods superweapon.
see_also: [DropPodInfantryMinimum, "system:drop-pods"]
---

Each superweapon firing randomly chooses an inclusive count between [`DropPodInfantryMinimum`](/keys/droppodinfantryminimum/) and this value. This affects only the superweapon's elite `E1`/`E2` squad, not [`Droppod=yes`](/keys/droppod-teamtype/) TeamTypes.

A value below the minimum still works: the random pick reorders the pair, so the chosen count always falls between the two values.

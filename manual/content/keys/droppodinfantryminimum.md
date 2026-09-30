---
key: DropPodInfantryMinimum
summary: Lower bound for the number of infantry requested by the Drop Pods superweapon.
see_also: [DropPodInfantryMaximum, "system:drop-pods"]
---

Each superweapon firing randomly chooses an inclusive count between this value and [`DropPodInfantryMaximum`](/keys/droppodinfantrymaximum/). This affects the superweapon's elite `E1`/`E2` squad only; it does not change the size of [`Droppod=yes`](/keys/droppod-teamtype/) TeamTypes.

The delivered count can be lower than the requested count. The whole squad shares one budget of `3 * count` placement attempts, and an infantry object is discarded when no legal nearby cell is found; [the superweapon entry path](/systems/drop-pods/#drop-pods-superweapon) documents the placement flow.

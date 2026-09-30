---
key: Tiberium
scope: overlaytype
label: Tiberium overlay
see_also: ["system:tiberium", "ChainReaction", "Image"]
when_omitted:
  kind: value
  value: "no"
---

Setting the flag rewrites two of the overlay type's own settings once its section has been read: its armor becomes wood, and a [`Land=Clear`](/keys/land/) overlay is promoted to the `Tiberium` [land type](/reference/enums/land-type/), which is the ground condition every harvesting test reads. An overlay left on another land type keeps it and is never harvested.

The flag also makes the overlay eligible for the reverse lookup that decides which registered Tiberium type a cell belongs to; an overlay carrying the flag that falls outside every type's overlay range is reported as the first registered type.

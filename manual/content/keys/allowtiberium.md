---
key: AllowTiberium
summary: Lets Tiberium take root on the tiles of a theater tile set.
see_also: ["system:tiberium"]
when_omitted:
  kind: value
  value: "no"
---

The value is read once per tile set and applied to every tile the set produces. It is the last test a cell makes before [accepting new growth](/systems/tiberium/#spread), so a tile set left at `no` refuses growth however clear the cell is otherwise. Tiberium already placed on such a tile stays where it is; only new growth is refused.

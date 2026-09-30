---
key: ClearTile
summary: Tile set holding a theater's plain clear ground, used as the substitute for a cell that has no tile.
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is selected, so the role stays unresolved.
---

Clear ground has no blend family of its own — it is what the other families blend *against* — but its first tile is the one the engine substitutes whenever a cell has no tile at all. Such a cell borrows it for its map preview color, its radar color, and the tile it draws with. Leveling terrain flat writes it into every cell that comes out unramped, and a map that gives no `[Map] Fill=` value, or gives any value other than `Water`, is filled with it before anything else is placed.

:::caution[The fill is stamped before the theater is read]
`[Map] Fill=` is applied while reading the map, ahead of the `[Map] Theater=` value and the theater control file that resolves this role. The tile stamped is therefore the one the previously loaded theater resolved, not this map's.
:::

:::note[The clear-ground test does not consult this role]
Asking whether a cell is clear ground answers yes for a cell with no tile and for the tile at index 0 — the first tile the theater loaded — whatever number this key resolves to. Pointing the role at any set other than the theater's first leaves the two disagreeing.
:::

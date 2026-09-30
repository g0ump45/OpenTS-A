---
key: ShadowCaster
summary: Tile set whose tiles darken the cells below them with a cliff shadow.
see_also: [ShadowTiles, TilesInSet]
when_omitted:
  kind: value
  value: "no"
---

A set carrying the flag registers the index of its first tile in a table of shadow-casting sets, and its tiles are marked as casters — but only if [`ShadowTiles`](/keys/shadowtiles/) also gives a non-zero figure. Without that, the set takes up a table slot and no tile of it ever casts anything.

What a marked tile draws is not chosen from the artwork of the set. The engine keeps a fixed table of forty shadow descriptions, indexed by a tile's distance from the first tile of the caster set it matched, and each entry names a frame of the shared cell-shadow shape, the sub-tile the shadow belongs on, and where to place it. Only positions 20 through 32 of that table carry a frame, and those same positions carry the list of cells to mark as overshadowed so that they redraw along with the cliff. A tile at any other position is marked as a caster, is asked for a shadow, and draws nothing. The shadow is also drawn only on the sub-tile the entry names, so a cell showing a different sub-tile of the same tile gets none.

```ini title="TEMPERAT.INI"
[TileSet0010]        ; example cliff set
SetName=Cliffs
FileName=CLIFF
TilesInSet=40
ShadowCaster=yes
ShadowTiles=40
```

:::danger[A theater may declare only five shadow-casting sets]
Nothing counts the caster sets a theater declares. A sixth set carrying the flag writes a sixth entry past the end of that five-entry table, into whatever static storage follows it. Nothing ever reads that entry back either — the lookup scans five slots — so a sixth caster set casts no shadow of its own and damages the engine's static data on the way. The count is taken over the whole theater control file, including sets whose `ShadowTiles` figure leaves their tiles casting nothing.
:::

:::caution[Caster sets within forty tiles of each other are confused]
A tile looks itself up by walking the caster table from the first slot and taking the first set it lies within forty tiles of. Where two caster sets are loaded close together, tiles of the later one fall inside that range of the earlier one and are given the earlier set's shadow description instead of their own.
:::

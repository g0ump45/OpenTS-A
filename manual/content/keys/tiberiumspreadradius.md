---
key: TiberiumSpreadRadius
summary: Selects which of the eight cells around a landing animation can take Tiberium.
see_also: ["IsTiberium", "TiberiumSpawnType", "system:tiberium"]
when_omitted:
  kind: value
  value: "0"
---

The setting is read only where the animation also declares [`IsTiberium=yes`](/keys/istiberium/#scope-animtype) and is thrown by [`Bouncer=yes`](/keys/bouncer/) or [`IsMeteor=yes`](/keys/ismeteor/#scope-animtype).

The growth is laid out by walking a square of offsets from minus the setting to plus it and discarding those that fall outside the radius. What each surviving offset then selects is not the cell it points at but the neighbor of the impact cell in the compass direction its first coordinate numbers, taken around the eight and wrapping. The reach is therefore never wider than the ring of eight cells touching the impact, and the cell the animation actually came down on is never planted at all.

| Setting | Cells that can take Tiberium |
| --- | --- |
| `0` | north |
| `1` | northwest, north, northeast |
| `2` | west through east across the north |
| `3` | southwest through southeast across the north |
| `4` and above | all eight neighbors |

Raising the figure past `4` adds nothing but work: the same eight cells are examined more times each, and a cell that has already germinated holds an overlay and is refused on every later visit.

:::caution[The default still plants]
`0` does not mean no spread. It keeps the single offset at the origin, which selects the first compass direction, so an animation flagged for Tiberium and left without this setting plants one cell to the north of where it landed. Every crystal and debris animation in the shipped `art.ini` that plants Tiberium either sets `0` or leaves the setting out.
:::

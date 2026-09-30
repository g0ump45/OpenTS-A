---
key: RampBase
summary: Tile set holding the twenty plain ramps that carry ground between height levels.
see_also: [RampSmooth, MMRampBase, SlopeSetPieces, CliffRamps]
when_omitted:
  kind: value
  value: "-1"
  note: The role stays unresolved, because no tile set number can match it, and every shape but the first derives a tile index landing somewhere in the theater's first nineteen tiles.
---

The set holds one piece per ramp shape, in the order the ramp shapes are numbered, so the tile for a given shape is this role plus the shape number minus one. Whenever the engine has decided what shape a cell's ground should be and needs the artwork for it, that is the arithmetic it does. [Theater control files](/formats/theater-control/) explains how a `[General]` role is resolved to a live tile index.

Four paths do it. A crater smooths its rim into ramps after terrain is deformed; a veinhole monster dishes the nine cells around itself the same way as it takes root; the transition pass restores the plain piece to a ramp cell whose neighbors along the ramp's axis are ramps as well, taking a piece from [`RampSmooth`](/keys/rampsmooth/) when they are not; and stamping certain pieces of [`SlopeSetPieces`](/keys/slopesetpieces/) substitutes a plain ramp for them on the affected subtiles. Random map generation uses the same arithmetic throughout its terrain pass.

:::danger[The derived tile index is never checked]
None of those paths test that the role resolved before writing the index into a cell, and the cell hands that index straight to the tile heap. With the role unresolved every ramp lands two tiles below where its shape number points, and the first shape writes `-1`. Pointing the key at the first missing tile set number instead resolves it to an index one place past the last tile loaded, which is out of range for every shape.
:::

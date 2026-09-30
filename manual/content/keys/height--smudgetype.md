---
key: Height
scope: smudgetype
label: Smudge rows
see_also: ["Width", "Crater", "Burn"]
when_omitted:
  kind: value
  value: "1"
---

The figure is how many rows of cells the smudge covers. Every cell in the block it would cover has to be flat, unmarked ground that takes a smudge — no ramp, no smudge already, no overlay, and a [`Morphable=yes`](/keys/morphable/) tile — or the smudge is rejected before it is placed; only the origin cell is checked against the map bounds. The block is then stamped one cell at a time, and every cell draws the same first frame of the artwork, shifted back to the block's origin, so one image covers the block rather than a frame per cell.

The figure also sorts craters and scorches into two groups. Only a smudge whose columns and rows are both above one counts as a large one, which is the group a large blast draws from; a small blast draws from the one-by-one smudges, and once the blast measures more than 48 pixels wide and more than 40 pixels tall the size test stops applying at all, so every smudge that can be placed at the spot is eligible.

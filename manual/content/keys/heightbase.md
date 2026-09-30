---
key: HeightBase
summary: Tile set number that is resolved and never read.
no_effect: true
see_also: [RampBase, SlopeSetPieces]
when_omitted:
  kind: value
  value: "-1"
  note: The role stays unresolved, because no tile set number can match it.
---

The value is resolved to a live tile index alongside every other `[General]` role of the theater control file.

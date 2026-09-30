---
key: MinZVel
scope: voxelanimtype
label: Voxel debris launch speed
see_also: ["MaxZVel", "MaxXYVel", "IsMeteor"]
when_omitted:
  kind: value
  value: "3.5"
---

Leptons per frame: 256 leptons to a cell, 15 frames to the second. Debris is thrown upward at this speed plus a whole number of leptons drawn from the span up to [`MaxZVel`](/keys/maxzvel/), so this is the slowest launch the type can produce, and the only one it produces where the maximum stands less than a lepton above it.

A meteor takes the figure as its vertical speed outright, with no pick and no reference to the maximum. The sign then decides the approach, as [`IsMeteor`](/keys/ismeteor/#scope-voxelanimtype) describes.

---
enum_id: BSizeType
slug: building-foundation
title: Building foundation
summary: Fixed cell footprints accepted by building Foundation settings.
representation: token
bindings:
  key_value_types: [BSizeType]
  scripting_parameter_types: []
source_files: [code/bsize.hh, code/ccini.cpp]
values:
  - { constant: BSIZE_11, value: 0, input: "1x1", meaning: "One cell wide by one cell tall." }
  - { constant: BSIZE_21, value: 1, input: "2x1", meaning: "Two cells wide by one cell tall." }
  - { constant: BSIZE_12, value: 2, input: "1x2", meaning: "One cell wide by two cells tall." }
  - { constant: BSIZE_22, value: 3, input: "2x2", meaning: "Two cells wide by two cells tall." }
  - { constant: BSIZE_23, value: 4, input: "2x3", meaning: "Two cells wide by three cells tall." }
  - { constant: BSIZE_32, value: 5, input: "3x2", meaning: "Three cells wide by two cells tall." }
  - { constant: BSIZE_33, value: 6, input: "3x3", meaning: "Three cells wide by three cells tall." }
  - { constant: BSIZE_35, value: 7, input: "3x5", meaning: "Three cells wide by five cells tall." }
  - { constant: BSIZE_42, value: 8, input: "4x2", meaning: "Four cells wide by two cells tall." }
  - { constant: BSIZE_33_REF, value: 9, input: "3x3Refinery", meaning: "Special three-by-three refinery footprint." }
  - { constant: BSIZE_13, value: 10, input: "1x3", meaning: "One cell wide by three cells tall." }
  - { constant: BSIZE_31, value: 11, input: "3x1", meaning: "Three cells wide by one cell tall." }
  - { constant: BSIZE_43, value: 12, input: "4x3", meaning: "Four cells wide by three cells tall." }
  - { constant: BSIZE_14, value: 13, input: "1x4", meaning: "One cell wide by four cells tall." }
  - { constant: BSIZE_15, value: 14, input: "1x5", meaning: "One cell wide by five cells tall." }
  - { constant: BSIZE_26, value: 15, input: "2x6", meaning: "Two cells wide by six cells tall." }
  - { constant: BSIZE_25, value: 16, input: "2x5", meaning: "Two cells wide by five cells tall." }
  - { constant: BSIZE_53, value: 17, input: "5x3", meaning: "Five cells wide by three cells tall." }
  - { constant: BSIZE_44, value: 18, input: "4x4", meaning: "Four cells wide by four cells tall." }
  - { constant: BSIZE_34, value: 19, input: "3x4", meaning: "Three cells wide by four cells tall." }
  - { constant: BSIZE_64, value: 20, input: "6x4", meaning: "Six cells wide by four cells tall." }
  - { constant: BSIZE_00, value: 21, input: "0x0", meaning: "Zero-cell footprint." }
---

A name is looked up rather than read as a pair of dimensions, so nothing works a block of cells out from the digits and a size not on this list resolves to `1x1`: `Foundation=7x7` gives a single-cell object rather than a footprint of another shape. The block a name stands for is also not the same for every object: a structure has a cell list for all twenty-two, while a TerrainType has one only for the first eight, which [`Foundation`](/keys/foundation/#scope-terraintype) covers.

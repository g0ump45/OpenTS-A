---
title: Validate Tiberium overlay frames before drawing
category: fix
release: 0.1.0
targets:
- type: system
  id: tiberium
  effect: changed
credit: [ZivDero]
---

A Tiberium cell whose stored stage lies outside the selected flat or slope SHP now omits that overlay and its shadow. Drawing and redraw-rectangle calculation validate the artwork's visible-frame count instead of indexing beyond its frame table.

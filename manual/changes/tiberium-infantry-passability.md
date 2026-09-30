---
title: Use terrain data for Tiberium infantry passability
category: fix
release: 0.1.0
targets:
- type: system
  id: movement-and-terrain
  effect: changed
credit: [ZivDero, AlexB]
---

Infantry passability over Tiberium now comes from the cell's land type and its `Foot` movement figure for every overlay image family. The former hard-coded refusal of the fourth Tiberium overlay range no longer overrides that terrain data.

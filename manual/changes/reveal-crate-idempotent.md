---
title: Keep repeated reveal crates revealing
category: fix
release: 0.1.0
targets:
- type: system
  id: crates
  effect: changed
credit: [ZivDero, Rampastring]
---

Collecting a Reveal crate for the locally controlled house now reveals the map even when that house already has full vision. Repeated Reveal crates no longer restore shroud; the Darkness result remains the crate path that reshrouds the map.

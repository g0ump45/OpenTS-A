---
title: Hold the laser wave inside the view
category: fix
release: 0.1.0
targets: []
credit: [ZivDero]
---

A laser or disruptor-style beam drawn against the edge of the view no longer risks a
crash at the highest detail level. The beam brightens the pixels it covers in place, and
its usual drawing walk could run one row below and one column beyond the view, writing
past the end of the frame when the view's bottom row was the frame's last. The walk now
covers exactly the view, which also lets its fallback path — used when the wave runs
past the depth buffer — reach the view's edge instead of stopping two pixels short.

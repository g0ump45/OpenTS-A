---
title: Repaint every cell flagged for redraw
category: fix
release: 0.1.0
targets: []
credit:
- ZivDero
---

Every cell flagged for repainting is repainted. A frame that is not a full redraw refreshes
only the cells something has changed, and the list of them held eight hundred, so a frame
that changed more than that left the remainder showing their previous picture. A cell was
also marked as dealt with before the list was consulted, which cost it its second chance
that frame, so the stale picture stood until something flagged the cell again or the whole
view was redrawn.

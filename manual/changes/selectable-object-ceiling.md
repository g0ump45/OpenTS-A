---
title: Let every object drawn on screen be clicked and band selected
category: fix
release: 0.1.0
targets: []
credit:
- ZivDero
---

Anything drawn in the tactical view can be clicked on and caught by a rubber band. Objects
put themselves on a list of what is on screen as they draw, and that list held five hundred
of them, so on a screen carrying more than that the ones drawn last went unrecorded.
Clicking one of those selected whatever else stood on the cell, or nothing at all, and a
rubber band drawn across them passed them over. The list now holds as many as the view
draws.

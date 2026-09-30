---
title: Release the cell a unit really occupied
category: fix
release: 0.1.0
targets: []
credit: [ZivDero, tomsons26]
---

A unit or infantryman leaving a cell now releases the same claim it took when it entered.
Both release routines decided between the ground and the bridge deck on height alone, while
the routines that take the claim also require the cell to have a bridge over it. Anything
that stood high above a cell with no bridge — a landing jumpjet, a paradrop coming down —
therefore claimed the ground and released the deck, leaving the ground spot marked as
occupied for the rest of the scenario and refusing pathfinding through it.

---
title: Deny grounded zero-ammo aircraft attack orders
category: fix
release: 0.1.0
targets:
- type: system
  id: aircraft-operations
  effect: changed
credit: [ZivDero, dkeeton]
---

A player can no longer issue an attack order to an aircraft that has no ammunition and is not airborne. Airborne aircraft and grounded aircraft holding ammunition continue through the ordinary player-fire eligibility checks.

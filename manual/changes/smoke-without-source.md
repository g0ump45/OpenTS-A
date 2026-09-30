---
title: Keep unattached smoke systems running
category: fix
release: 0.2.0
targets:
- type: system
  id: particle-systems
  effect: changed
credit:
- GEARS0FUMP45
---

Smoke systems without a source object keep their existing position and continue
updating particles. Smoke_AI checks for a source before following it or checking
whether it is travelling through a tunnel. This fixes a null pointer crash when
a mission begins after its cutscene. Attached smoke behavior, particle type
settings and save layouts are unchanged.

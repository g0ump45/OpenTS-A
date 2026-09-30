---
title: Reacquire stale Guard targets
category: fix
release: 0.1.0
targets:
- type: system
  id: target-selection
  effect: changed
credit: [ZivDero, dkeeton, Rampastring]
---

Non-engineer ground objects and human-controlled aircraft on Guard now revalidate an existing target against the guard-range scan and can replace one that is no longer legal or nearby. Computer-controlled aircraft retain their existing Guard target, while engineers continue to skip the scan.

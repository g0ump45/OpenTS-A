---
title: Skip scenario records without a live owner
category: fix
release: 0.1.0
targets:
- type: format
  id: scenario-objects
  effect: changed
credit: [ZivDero]
---

Scenario object rows and trigger definitions now require their registered HouseType to have a live house in the current session. Rows without one are skipped before construction, links to missing or rejected triggers remain empty, and tags that name them remain inert. Vehicle follower IDs are resolved through the original `[Units]` row positions, so skipping or failing to place one row no longer redirects another vehicle's follower link through a compacted runtime list.

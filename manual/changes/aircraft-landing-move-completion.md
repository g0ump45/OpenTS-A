---
title: Finish aircraft moves after landing completes
category: fix
release: 0.1.0
targets:
- type: system
  id: aircraft-operations
  effect: changed
credit: [ZivDero, hifi]
---

An aircraft following the normal move path now remains in its approach or landing state while its movement controller is still moving, even after it enters the destination cell. The move becomes idle only after movement stops or follows the existing landing-zone recovery path when the destination becomes unsuitable.

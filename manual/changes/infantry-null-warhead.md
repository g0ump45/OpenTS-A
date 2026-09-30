---
title: Apply infantry damage safely without a warhead
category: fix
release: 0.1.0
targets:
- type: system
  id: destruction-and-debris
  effect: changed
credit: [ZivDero]
---

Infantry damage no longer dereferences a missing warhead. The shared damage path still decides the result: ordinary damage without a warhead is reduced to nothing, while forced damage is applied at its raw value. With no warhead there is no prone-damage multiplier, web paralysis or specialized infantry death, so a killing forced hit uses the ordinary infantry removal path.

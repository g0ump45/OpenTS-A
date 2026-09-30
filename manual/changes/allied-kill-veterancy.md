---
title: Exclude allied kills from veterancy
category: fix
release: 0.1.0
targets:
- type: system
  id: veterancy
  effect: changed
credit: [ZivDero, AlexB]
---

A trainable object no longer earns experience for destroying an object whose house considers the killer allied. Kill scores, loss records, trigger processing, and the last-attacker record remain unchanged.

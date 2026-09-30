---
key: CivEvac
summary: Parsed flag that is thrown away as it is read.
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

The assignment is read from the scenario's `[Basic]` section and the result is discarded on the spot: it is stored nowhere, and the scenario has no member for it to be stored in. The map editor goes further and deletes the entry from any scenario it writes back out, so a map that carries one loses it at the next save.

No gameplay path reads it.

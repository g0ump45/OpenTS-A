---
key: Adjacent
summary: How far this building searches for an eligible anchor while it is being placed.
see_also: [BaseNormal, "system:base-adjacency"]
---

```ini title="rules.ini"
[GAPOWR]
Adjacent=5
```

While the player places `GAPOWR`, this value controls how far the pending foundation searches for an owned building with [`BaseNormal=yes`](/keys/basenormal/). It does not define a radius projected by an already placed `GAPOWR`.

:::note[Zero still allows touching placement]
The scan adds one cell to the stored value. With `Adjacent=0`, an eligible anchor may still be found directly beside the pending foundation.
:::

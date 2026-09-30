---
key: BaseNormal
summary: Whether this placed building can anchor later building placements.
see_also: [Adjacent, "system:base-adjacency"]
---

```ini title="rules.ini"
[GAPOWR]
BaseNormal=no
```

With this assignment, a placed `GAPOWR` is not an eligible anchor when the player places another building. The setting belongs to the existing candidate anchor; it does not set a projected radius.

The building being placed supplies the search distance through [`Adjacent`](/keys/adjacent/).

:::caution[NAFNCE and NAPOST are overridden]
After reading this key, the engine forces both IDs to `BaseNormal=no`.
:::

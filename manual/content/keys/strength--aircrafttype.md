---
key: Strength
scope: aircrafttype
label: Maximum strength
---

```ini title="rules.ini"
[GAPOWR]
Strength=800
```

This scope sets the type's maximum-strength value. A damageable runtime instance created from the type starts with that value as its current strength, and damage reduces the current value.

:::caution[HMEC is overridden]
After reading `[HMEC]`, the engine sets its maximum strength to `1200`. Changing `Strength=` in that section does not change the final value.
:::

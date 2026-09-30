---
key: SuspendPriority
summary: The TeamType priority a team must reach to survive a base attack.
see_also: ["system:base-attacked", Priority, SuspendDelay]
when_omitted:
  kind: value
  value: "20"
---

When a call-up runs for a computer house, every team that house owns whose TeamType [`Priority`](/keys/priority/#scope-teamtype) is strictly below this value has all of its members removed and is suspended, freeing them to be [called back as defenders](/systems/base-attacked/#teams-are-emptied-first). A team at or above the value keeps its members and carries on. The value is compared against the TeamType's own priority, not against any per-house or per-difficulty figure.

```ini title="rules.ini"
[General]
SuspendPriority=6 ; a team on the default Priority of 7 now survives a base attack
```

:::caution[The stock priority sits below the stock threshold]
A TeamType that does not state a priority is treated as `7`, and this key's stored default is `20`, so with neither key written every team of the attacked house is stripped every time a call-up actually runs — which the six refusals ahead of it make rarer than any damage. Either raise this threshold above the priorities that should keep running, or give those TeamTypes a priority above it.
:::

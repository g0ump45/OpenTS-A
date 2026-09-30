---
key: MCVDeploy
summary: Parsed flag that the engine never uses.
no_effect: true
see_also: [UndeploysInto]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The name promises the option that lets a construction yard fold back into the vehicle it came from. Nothing in the game asks for the flag: it is parsed into the scenario's special options and written back out by the map editor, and no gameplay path reads it.

Undeploying is decided by the structure type instead, through [`UndeploysInto`](/keys/undeploysinto/).

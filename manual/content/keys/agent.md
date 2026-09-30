---
key: Agent
summary: Makes a soldier report on the structure it walks into rather than capturing it.
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: "no"
---

The spy branch runs only for a soldier that is not an [`Engineer=yes`](/keys/engineer/#scope-infantrytype) type, because the engineer handling claims the arrival first and never falls through to it. A type that sets both flags therefore behaves as an engineer and never spies.

This setting forces nothing else on. Without [`Infiltrate=yes`](/keys/infiltrate/) in the same section the soldier is never offered a structure as a target or a destination and never reaches the branch at all, so the two are written together. [What a spy gains](/systems/capture/#infiltrating-it) covers the radar and display effects that follow.

---
key: Official
scope: scenarios
label: Unused copy
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

The entry is read a first time at the very start of the scenario load, before the theater is chosen or the rules are prepared. That copy is placed in a local variable, immediately assigned to itself to keep the compiler quiet, and never looked at again; no gameplay path reads it.

The copy that does decide something is [read again much later](/keys/official/#scope-scenarios-2), from the same assignment.

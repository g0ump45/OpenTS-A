---
key: TiberiumHeal
scope: global-rules
label: Healing interval
see_also: ["system:repair"]
when_omitted:
  kind: value
  value: ".0167"
---

The value is a fraction of a minute, multiplied by 900 frames and truncated, giving one healing step every 15 frames at the default. The test is against the global frame counter, so every object standing in Tiberium with [`TiberiumHeal=yes`](/keys/tiberiumheal/#scope-aircrafttype) is healed on the same frames. A value between zero and `1/900` truncates to a zero interval and crashes the game the moment a damaged object with the flag occupies Tiberium.

---
key: TurboBoost
scope: weapontype
label: Per-weapon flag
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

The engine parses this yes/no flag into each weapon and stores it. No gameplay path reads the stored flag, and the [global multiplier](/keys/turboboost/#scope-global-rules) that shares the name has no reader either.

---
key: TiberiumExplosive
scope: scenarios
label: Scenario flag
no_effect: true
see_also: ["system:tiberium"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The value is stored with the other scenario flags and never consulted. The spelling that makes a loaded harvester explode is the [`[CombatDamage]` entry](/keys/tiberiumexplosive/#scope-global-rules).

---
key: Visceroids
summary: Parsed flag that spawns nothing.
no_effect: true
see_also: [TiberiumDeathToVisceroid, SmallVisceroid]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The name promises the visceroids that rise from infantry killed in Tiberium. The flag is parsed with the rest of the scenario's special options and never consulted, so no gameplay path reads it. The switch that actually decides whether those deaths leave a visceroid behind is [`TiberiumDeathToVisceroid`](/keys/tiberiumdeathtovisceroid/) in the map's `[Basic]` section.

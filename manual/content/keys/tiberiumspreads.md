---
key: TiberiumSpreads
summary: Allows a ripe Tiberium cell to seed its neighbors.
see_also: ["system:tiberium", "TiberiumGrowthEnabled", "SpreadPercentage"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, yes.
---

The switch is the first test a cell makes before it may [spread](/systems/tiberium/#spread); with it off, cells still ripen but never seed bare ground.

:::caution[The entry is read in campaigns only]
The `[SpecialFlags]` block is read from the map only in a single-player mission or with the map debugger active. Every multiplayer and skirmish game forces this switch on when the scenario starts.
:::

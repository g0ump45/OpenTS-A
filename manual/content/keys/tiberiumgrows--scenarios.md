---
key: TiberiumGrows
scope: scenarios
label: Fast growth
see_also: ["system:tiberium", "Growth", "TiberiumGrowthEnabled"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

Each type's [`Growth`](/keys/growth/) delay is multiplied by `0.3` when it is reloaded, which is the whole of the switch's effect. It does not decide whether Tiberium grows: growth runs at the full delay with the switch off and stops only when [`TiberiumGrowthEnabled=no`](/keys/tiberiumgrowthenabled/).

:::caution[The entry is read in campaigns only]
The `[SpecialFlags]` block is read from the map only in a single-player mission or with the map debugger active. A network lobby switches fast growth on for the game it launches; a skirmish keeps the program's own default of off — inheriting whichever state the last lobby in the same session left behind — so its growth runs at the full delay. The map's entry is ignored in both.
:::

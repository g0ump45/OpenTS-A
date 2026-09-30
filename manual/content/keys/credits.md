---
key: Credits
summary: The money a scenario's house begins a campaign mission with, counted in hundreds.
see_also: [Money, CarryOverMoney, CarryOverCap]
when_omitted:
  kind: value
  value: "0"
  note: The read substitutes a literal zero rather than keeping any figure the house already held.
---

The value is multiplied by 100 as it is stored, so `Credits=50` is five thousand credits. It fills both the house's spendable balance and its record of what it started with.

```ini title="scenario map file"
[GDI] ; a house record in the scenario's own house list
Credits=50
```

Only a campaign mission reads its house records at all, so this is a campaign setting. A skirmish or multiplayer house takes its opening balance from the session's own starting-credits option instead.

The second copy is what the mission's efficiency rating on the score screen divides by: the house's remaining money is measured against everything it started with plus everything it harvested. [Carry-over money](/keys/carryovermoney/) granted at the start of the next mission is added to that record as well as to the balance, so it counts as starting money rather than as income.

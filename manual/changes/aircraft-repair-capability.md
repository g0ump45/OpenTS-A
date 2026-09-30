---
title: Use repair capability for player aircraft actions
category: fix
release: 0.1.0
targets:
- type: system
  id: repair
  effect: changed
- type: key
  id: UnitRepair
  effect: changed
- type: key
  id: RepairBay
  effect: changed
credit: [ZivDero, Iran]
---

A selected player-controlled aircraft now receives the enter action for any idle, empty `UnitRepair=yes` building or helipad. Other repair buildings previously needed to be the exact type named by `RepairBay`, and an allied building could be presented as a move action before this check. Repair orders and computer-controlled aircraft continue to use `RepairBay`.

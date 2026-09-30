---
key: Value
summary: Credits paid for each growth stage of a Tiberium type.
see_also: ["system:tiberium"]
when_omitted:
  kind: value
  value: "0"
---

A cell is worth this figure multiplied by its growth stage plus one, so a fully ripened cell of a twelve-stage overlay set is worth twelve times the setting. That worth is what the [harvester's patch search](/systems/tiberium/#finding-a-patch) ranks candidate cells by.

A harvester stores growth stages rather than credits. For most houses a stored unit is converted at this value only when the house spends it, so changing the setting re-prices Tiberium already sitting in a silo. A computer house in a skirmish or multiplayer game is the exception, converting each unit as it is handed over and never storing it, which puts that house's income beyond any later change to the figure.

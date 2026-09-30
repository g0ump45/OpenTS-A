---
key: DamageDelay
summary: Minutes between the damage ticks a house takes while it is short of power.
see_also: ["system:power"]
when_omitted:
  kind: value
  value: "1"
---

The timer runs for every house and is reloaded with this many game minutes each time it expires, whether or not the house was short of power at that moment. Only when it expires and the house cannot meet its drain does the [structure damage tick](/systems/power/#the-structure-damage-tick) run, so the value sets the cadence and never the condition. A house is first charged the delay when it is created.

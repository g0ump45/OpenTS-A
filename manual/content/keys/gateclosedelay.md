---
key: GateCloseDelay
summary: The time in game minutes a gate stands open once its footprint is clear.
see_also: ["system:walls-and-gates", "Gate"]
when_omitted:
  kind: value
  value: "0"
---

```ini title="rules.ini"
[GAGATE_A] ; example gate BuildingType
Gate=yes
GateCloseDelay=.03
```

A game minute is 900 frames, so the fragment above holds the gate open for 27 frames after the last thing steps out of its footprint. At the default the gate begins closing on the first pass after its footprint is clear.

The timer is reloaded from scratch on every pass while anything other than the gate itself stands anywhere in the footprint, so the delay never runs while traffic is crossing. Only a gate still in its open state is held that way: once the door has begun closing, an object entering the footprint neither reloads the timer nor reverses it. Only a [`Gate=yes`](/keys/gate/) BuildingType reads the value; the travel time of the door itself is [`DeployTime`](/keys/deploytime/).

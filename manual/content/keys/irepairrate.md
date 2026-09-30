---
key: IRepairRate
summary: The interval between servicing steps inside a hospital, and an armory's promotion delay.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: ".016"
---

A hospital or an armory counts servicing steps while it holds an infantry and acts each time the count reaches this value multiplied by 900, so a larger value keeps the occupant inside longer. A hospital heals one step per elapse and releases the occupant once it reaches full strength; an [`Armory=yes`](/keys/armory/) building [promotes the occupant](/systems/veterancy/#promotion-without-kills) and releases it at the first elapse.

The setting is shared by both building kinds and cannot be tuned for one without the other. Vehicle service depots keep their own timing.

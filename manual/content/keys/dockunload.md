---
key: DockUnload
summary: Lets a Tiberium harvester dock at a building and unload there.
see_also: ["system:tiberium", "Dock", "Refinery"]
when_omitted:
  kind: value
  value: "no"
---

This is the flag a building answers a harvester's docking request with, and it is the only one that admits a Tiberium harvester: [`Refinery=yes`](/keys/refinery/) supplies the dock point and the unloading animations but grants no access on its own. The harvester must belong to the same house as the building or each house must declare the other an ally; a one-way alliance is refused. A [weed refinery](/systems/veins/) is the exception: it admits a weeder on [`Weeder=yes`](/keys/weeder/) alone, without this flag. A building already holding an attached object refuses the request until that object leaves.

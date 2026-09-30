---
key: MaximumQueuedObjects
summary: The most entries a production queue may hold.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "5"
---

The count is of entries waiting behind the object under construction, not of objects outstanding, so a house can have this many plus one on order for each kind of object. An order that would exceed it is dropped and plays [`ScoldSound`](/keys/scoldsound/) for a player-controlled house.

Structures are never queued, so the value has no bearing on them; [the queue](/systems/production/#the-queue) covers what a second structure order does instead.

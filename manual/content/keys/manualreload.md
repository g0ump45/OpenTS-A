---
key: ManualReload
summary: Stops the type from arming its reload delay when it fires, and has a service depot refill its magazine for free.
see_also: ["system:repair"]
when_omitted:
  kind: value
  value: "no"
---

A vehicle firing normally arms a 450-frame reload delay, which refills the magazine of one that fires only while standing still; this flag suppresses that arming. What replaces it is the service depot, which fills the magazine to full in a single exchange and charges nothing for it.

The refill pre-empts the repair step for that exchange, so a damaged carrier of this flag rearms first and starts repairing afterwards. An undamaged one is still admitted rather than turned away: it is rearmed on the spot and released. [What a depot does for free](/systems/repair/#what-a-depot-does-for-free) traces the order.

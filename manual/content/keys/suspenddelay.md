---
key: SuspendDelay
summary: Minutes a team stays suspended after a base attack emptied it.
see_also: ["system:base-attacked", SuspendPriority]
when_omitted:
  kind: value
  value: "2"
---

The team object is not destroyed when a base attack [suspends it](/systems/base-attacked/#teams-are-emptied-first): it is stripped of its members and then does nothing at all until this countdown expires. It does not resume: a team that had ever reached full strength is deleted at that moment, and one that never did gets a single pass at recruiting before the unfilled-team rules dissolve it outside a campaign. Every team the same attack suspends receives the same countdown, and a later attack while the countdown is still running restarts it from the top.

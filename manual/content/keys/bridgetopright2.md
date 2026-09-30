---
key: BridgeTopRight2
summary: Second position accepted as the top-right end of a north-south bridge span.
see_also: [BridgeTopRight1, BridgeMiddle2]
when_omitted:
  kind: value
  value: "-1"
  note: The position lands two tiles before the set's first piece rather than on a piece of it.
---

Every test that looks for the top-right end of a north-south span accepts this position or [`BridgeTopRight1`](/keys/bridgetopright1/), and no path distinguishes the two. A set with only one piece for that end may name the same position twice.

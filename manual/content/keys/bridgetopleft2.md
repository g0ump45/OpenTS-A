---
key: BridgeTopLeft2
summary: Second position accepted as the top-left end of an east-west bridge span.
see_also: [BridgeTopLeft1, BridgeMiddle1]
when_omitted:
  kind: value
  value: "-1"
  note: The position lands two tiles before the set's first piece rather than on a piece of it.
---

Every test that looks for the top-left end of an east-west span accepts this position or [`BridgeTopLeft1`](/keys/bridgetopleft1/), and no path distinguishes the two. A set with only one piece for that end may name the same position twice.

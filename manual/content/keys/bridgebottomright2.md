---
key: BridgeBottomRight2
summary: Second position accepted as the bottom-right end of an east-west bridge span.
see_also: [BridgeBottomRight1, BridgeMiddle1]
when_omitted:
  kind: value
  value: "-1"
  note: The position lands two tiles before the set's first piece rather than on a piece of it.
---

Every test that looks for the bottom-right end of an east-west span accepts this position or [`BridgeBottomRight1`](/keys/bridgebottomright1/), and no path distinguishes the two. A set with only one piece for that end may name the same position twice.

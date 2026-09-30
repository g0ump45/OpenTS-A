---
key: ZFudgeTunnel
summary: The depth bias applied to an object standing at a tunnel mouth.
see_also: ["ZFudgeBridge", "ZFudgeCliff", "ZFudgeColumn"]
when_omitted:
  kind: value
  value: "10"
---

The figure is offered as the object's depth bias whenever a tunnel mouth is judged to be in the way, and dropped otherwise; the multiplier is only ever 0 or 1, so the figure is used as written when it applies. The test finds the tunnel cell — the object's own, or its neighbor to the north or west — and then asks whether the cell two steps north or two steps west of that also holds a tunnel. An object riding a bridge deck is never fudged for a tunnel.

Only the largest of the four fudges applies at any moment, so this one has an effect only while it beats whatever [`ZFudgeBridge`](/keys/zfudgebridge/), [`ZFudgeCliff`](/keys/zfudgecliff/) and [`ZFudgeColumn`](/keys/zfudgecolumn/) are contributing. The winner is added to the bias the object's locomotor asks for and to a second bias the object works out for itself. The stock rules set it on the same 23 vehicles that carry a column figure, between 12 and 18.

---
key: ZFudgeCliff
summary: The depth bias applied to an object standing at the foot of a cliff.
see_also: ["ZFudgeBridge", "ZFudgeColumn", "ZFudgeTunnel"]
when_omitted:
  kind: value
  value: "10"
---

The figure is multiplied by a strength the engine works out from the ground to the south-east of the object, and the product is offered as the object's depth bias. One cell to the south-east standing four or more height levels above the object gives a strength of 2; two cells to the south-east doing so gives 1, and that second test overrides the first when both hold. Neither applies to an object riding a bridge deck, which is never fudged for a cliff.

Only the largest of the four fudges applies at any moment, so this one has an effect only while it beats whatever [`ZFudgeBridge`](/keys/zfudgebridge/), [`ZFudgeColumn`](/keys/zfudgecolumn/) and [`ZFudgeTunnel`](/keys/zfudgetunnel/) are contributing. The winner is added to the bias the object's locomotor asks for and to a second bias the object works out for itself.

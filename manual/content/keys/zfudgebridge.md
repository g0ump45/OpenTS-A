---
key: ZFudgeBridge
summary: The depth bias applied to an object while it is under a bridge.
see_also: ["ZFudgeCliff", "ZFudgeColumn", "ZFudgeTunnel"]
when_omitted:
  kind: value
  value: "0"
---

An object counts as under a bridge when its own cell is covered by one, or when it stands alongside a covered cell that the deck still reaches over — a covered cell to the north or south for an east-west bridge, or to the east or west for a north-south one. An object riding the deck itself never counts. While it counts, this figure is offered as the object's depth bias.

Unlike the other three fudges the figure is used as written, with no multiplier of its own. Only the largest of the four applies at any moment: [`ZFudgeCliff`](/keys/zfudgecliff/), [`ZFudgeColumn`](/keys/zfudgecolumn/) and [`ZFudgeTunnel`](/keys/zfudgetunnel/) each have their own condition, and the winner is added to the bias the object's locomotor asks for and to a second bias the object works out for itself. The stock rules raise it on three types only, from 2 on the Titan to 25 on the Mammoth Mk. II, and leave every other type at 0.

The four keys are accepted in an AircraftType, BuildingType, InfantryType or UnitType section, but only an aircraft, an infantryman or a vehicle has its depth biased this way. A structure never does.

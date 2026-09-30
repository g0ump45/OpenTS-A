---
key: GateStages
summary: The number of door frames a gate animates through.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "9"
---

The door's completion fraction is scaled by this count to pick the frame to draw, and the frame is clamped to the last one in the range. A gate at or below [`ConditionYellow`](/keys/conditionyellow/) draws from a second block of door frames offset by this count plus one, so the art needs both blocks.

For a [`Gate=yes`](/keys/gate/) type the same figure plus one is the buildup step count that [`BuildupTime`](/keys/builduptime/) is divided into, in place of the frame count the buildup art would otherwise supply.

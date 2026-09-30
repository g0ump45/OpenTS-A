---
key: Gate
summary: Makes the BuildingType a gate that opens for a unit wanting to pass.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "no"
---

A unit that wants to cross the cell asks the gate to open and waits until the door reports itself open; the gate then holds while anything is still in the way and closes afterwards. Any structure that is not a gate answers both questions as permanently open, so movement never waits on it.

Two drawing rules follow from the flag. The construction animation runs from its last frame back to its first, and the buildup step count that [`BuildupTime`](/keys/builduptime/) is divided into is [`GateStages`](/keys/gatestages/) plus one rather than half the frames in the buildup art.

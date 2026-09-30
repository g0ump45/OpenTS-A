---
key: GateDown
summary: The sound played at a gate as its door starts opening.
see_also: ["system:walls-and-gates", "Gate"]
when_omitted:
  kind: value
  value: none
---

The sound plays once, at the gate's own position, on the pass that starts the door moving open from rest. A door that was already closing when the gate is asked to open is reversed in place instead and plays nothing, and a gate asked to open while already open plays nothing either.

Despite the names, this is the opening sound and [`GateUp`](/keys/gateup/) is the closing one.

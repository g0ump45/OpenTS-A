---
key: IsCoreDefender
scope: unittype
label: Core defender vehicle
see_also: [SensorArray, "system:emp-pulse"]
when_omitted:
  kind: value
  value: "no"
---

Two unrelated things read the flag on a vehicle.

[An EM pulse](/systems/emp-pulse/#what-a-pulse-reaches) does not paralyze it. Every other vehicle inside the blast has its locomotor powered off, is stopped where it stands and is stunned for the pulse's duration; a flagged one keeps moving and only springs its paralyzed trigger event.

It is also drawn the way a structure is. A selected one — or one standing below ground on a cell a [sensor array](/keys/sensorarray/) has marked — takes the three-dimensional selection box and the pip bar laid along its near edge instead of the bracket and row of health pips every other vehicle gets, and the box is built on a vertical extent of 700 leptons rather than the 200 an ordinary vehicle carries.

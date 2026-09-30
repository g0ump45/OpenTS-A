---
key: Thief
summary: Makes a soldier take a non-allied vehicle it is walking toward.
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: "no"
---

This is not the setting behind the vehicle hijacker; [`VehicleThief=yes`](/keys/vehiclethief/) is, and the two are separate features with separate cursors and separate limits. They meet in one place: both stamp the vehicle with the type that took it, so the thief steps back out at the wreck when that vehicle dies. Nothing offers a cursor for this one. The steal runs on the soldier's own pass whatever mission it is on, and needs only a non-allied vehicle as its movement destination: within half a cell and one height level of it, the vehicle changes hands and the soldier is consumed. Further out the soldier keeps re-aiming at the vehicle as it moves.

The setting also [widens what its owner scans for](/systems/target-selection/#what-each-kind-of-object-considers), adding capturable structures and Tiberium processors to the request.

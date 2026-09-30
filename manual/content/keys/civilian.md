---
key: Civilian
summary: Counts the soldier as a civilian evacuation candidate and drops it from the surviving-infantry report.
see_also: [Nominal, Fraidycat, Disguised]
when_omitted:
  kind: value
  value: "no"
---

A soldier of such a type counts as a civilian evacuation unless it is a technician — the state an infantry of a [`Nominal=yes`](/keys/nominal/) type takes when a structure throws it out, on every sale but only on the destruction of a structure that has buildup artwork. Two behaviors hang off that test, and both belong to aircraft alone. An aircraft transport that one of these soldiers reports itself aboard is put on the Retreat mission at once, whatever it was doing before, and nothing follows from the assignment: an aircraft handles that mission itself and its handling does nothing, so the transport heads for no edge. The evacuation is a separate check. An aircraft on Retreat that is outside the playable area deletes every passenger it holds, and for each one that counts as a civilian evacuation it sets a flag on the *passenger's* house rather than the transport's; the flag is never cleared again. Nothing acts on it. [Civilians Evacuated](/mapping/events/tevent-evac-civilian/) is the only thing that reads the flag, that event is never announced to a trigger and so is never satisfied, and it would read the flag on the house owning the trigger rather than on the passenger's house in any case.

The setting carries no behavior of its own beyond that. Running from danger is [`Fraidycat=yes`](/keys/fraidycat/) and wearing another type's identity is [`Disguised=yes`](/keys/disguised/); neither follows from this one.

The surviving-infantry figures a multiplayer session reports at its end count every infantry a house still owns except these, so a civilian on the map is invisible to that tally.

---
key: GuardArea
summary: The IQ level at which a computer house leaves idle objects in Area Guard instead of Guard.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "4"
---

A house whose [`IQ`](/keys/iq/) is below this level puts idle objects into plain Guard, which scans only out to the object's guard radius and holds position. At or above it an armed object takes Area Guard instead, which scans out to twice the guard range — falling back to twice the longer weapon range when that is unset — from the spot it was left at and pursues what it finds; an unarmed engineer and an unarmed vehicle thief take Area Guard as well. A member of a team always takes plain Guard.

A vehicle carrying the `GUARD_AREA` ability takes Area Guard whatever the level says. For infantry the test is computer-only, but the vehicle path carries no such gate: a human house whose map-given `IQ` reaches this level sends its idle armed vehicles into Area Guard too.

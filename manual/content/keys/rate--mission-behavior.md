---
key: Rate
scope: mission-behavior
label: Mission servicing delay
see_also: ["system:repair"]
when_omitted:
  kind: value
  value: ".016"
---

The value is the fraction of a minute a mission waits between one servicing pass and the next, read from the mission's own rules section — `[Sleep]`, `[Guard]`, `[Repair]` and the rest — and multiplied out to 14 frames at the default. An idle service building counts its work in these passes; [an armory's promotion clock](/systems/repair/#hospitals-and-armories) is the visible case.

[`AARate`](/keys/aarate/) in the same section is the anti-aircraft counterpart, and it falls back to this value when it is absent or zero.

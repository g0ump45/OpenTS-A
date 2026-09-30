---
key: RepairDelay
summary: The wait a computer house takes between starting one building repair and starting the next.
see_also: ["system:repair"]
when_omitted:
  kind: value
  value: ".02"
---

A house that has just switched the wrench on somewhere in its base is barred from starting another repair until a timer expires, and the timer is picked at random between this value multiplied by 225 frames and this value multiplied by 1800 frames — 4 to 36 frames at the default. The wait spreads a base's repairs out; it does not slow a repair already running, which steps on [`RepairRate`](/keys/repairrate/) like any other.

Each difficulty section carries its own value, and a house takes the one for the difficulty slot it is assigned. A house under player control arms no timer at all, so if a map opens [the repair gate](/systems/repair/#when-the-computer-repairs) for the player, every damaged building it owns is put under the wrench in consecutive frames.

:::caution[A later file that carries the section resets this value]
The difficulty reader supplies a fixed `.02` rather than the value already in force, so a map that declares `[Easy]`, `[Normal]` or `[Difficult]` without repeating `RepairDelay` puts the setting back to `.02` instead of leaving the rules value alone.
:::

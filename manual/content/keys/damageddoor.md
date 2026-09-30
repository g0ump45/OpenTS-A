---
key: DamagedDoor
summary: Draws the factory door animation from a second block of frames once the structure is damaged.
see_also: ["DoorAnim", "DoorStages", "UnderDoorAnim"]
when_omitted:
  kind: value
  value: "no"
---

With the flag set, a structure at or below [`ConditionYellow`](/keys/conditionyellow/) has [`DoorStages`](/keys/doorstages/) added to the [`DoorAnim`](/keys/dooranim/) frame it would otherwise draw. The addition happens after the frame has been clamped into the healthy range, so the damaged block is a second run of the same length placed directly after the first.

The flag reaches nothing else. [`UnderDoorAnim`](/keys/underdooranim/) switches to its own damaged frame on the same health test whether or not this is set.

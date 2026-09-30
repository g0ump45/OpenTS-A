---
key: UnderDoorAnim
summary: The shape drawn beneath a structure's factory door while it unloads.
see_also: ["DoorAnim", "DoorStages", "DeployingAnim", "WeaponsFactory"]
when_omitted:
  kind: value
  value: ""
  note: No under-door shape is loaded and none is drawn.
---

The value is a filename without its extension, and only a non-empty value is taken. The named `<value>.SHP` is loaded with the rules, and refetched on the same occasions and with the same theater rewrite [`DoorAnim`](/keys/dooranim/) describes.

It is drawn while the structure is unloading, in the same pass as the structure itself and after it, at ground depth. The frame is chosen from health alone: frame `1` at or below [`ConditionYellow`](/keys/conditionyellow/) and frame `0` above it. [`DoorStages`](/keys/doorstages/) has no bearing on it, so the file needs exactly those two frames. Its brightness includes [`ExtraLight`](/keys/extralight/).

---
key: ScreenHeight
scope: client-settings
label: Stored height
see_also: [ScreenWidth, Fullscreen]
when_omitted:
  kind: unchanged
  note: The read passes through the height the display was already opened at, and nothing later overwrites it.
---

This is the later of the two reads of the assignment, made with the rest of the client settings once the display is already open. [`ScreenWidth`](/keys/screenwidth/#scope-client-settings) covers what the pair settles at that point: the mode the display options screen starts from, and the mode a scenario switches to where switching is allowed. Writing `-1` rather than leaving the assignment out is not the same thing, for the reason given there.

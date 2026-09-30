---
key: ScreenWidth
scope: client-settings
label: Stored width
see_also: [ScreenHeight, Fullscreen]
when_omitted:
  kind: unchanged
  note: The read passes through the width the display was already opened at, and nothing later overwrites it.
---

This is the later of the two reads of the assignment, made with the rest of the client settings once the display is already open. It cannot change the size of the screen the game is drawing on; what it settles is the size the display options screen starts from.

Accepting the display options screen stores the mode picked there, and leaving the options screen behind it writes the stored width back to `sun.ini`, so the file normally carries one once that screen has been used.

:::caution[Writing the fallback figure is not the same as leaving the assignment out]
An absent assignment lets the size the display opened at stand. A `-1` written into the file is read back over that size here, after the screen has already been sized around it, leaving the stored width at `-1`: no mode in the display options list matches it, and a scenario that switches modes is asked for a display of `-1` pixels.
:::

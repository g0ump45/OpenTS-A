---
key: Cameo
summary: The SHP file drawn as an object's sidebar cameo.
see_also: ["system:sidebar"]
when_omitted:
  kind: value
  value: ""
  note: No cameo file is selected and XXICON.SHP is drawn in the slot instead.
---

The value is the filename without its extension, and only a non-empty value is taken; a file that cannot be loaded leaves `XXICON.SHP` in the slot. The section this is read from is the object's [Image ID](/keys/image/), so two types pointed at the same art share a cameo unless one of them is given its own section.

[What a cameo shows](/systems/sidebar/#what-a-cameo-shows) covers the darkening, clock and captions drawn over it.

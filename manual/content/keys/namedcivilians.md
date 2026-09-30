---
key: NamedCivilians
summary: Flag intended to name civilian objects outright.
no_effect: true
see_also: [Nominal]
when_omitted:
  kind: value
  value: "no"
---

The flag is stored under its own member on the rules object and nothing anywhere reads that member back — not the tooltip that names the object under the cursor, not the sidebar, not the multiplayer synchronization checksum.

Whether an object is named or glossed over with a generic label is decided per type instead, by [`Nominal`](/keys/nominal/), which the tooltip consults on the object's type and, for a structure, on the runtime instance as well. Without it an enemy object is shown only as an enemy soldier, vehicle or structure.

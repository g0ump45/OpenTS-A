---
key: RadarEventVisibilityDurations
summary: The frames a settled radar event stays drawn, one entry per event kind.
see_also: ["system:map-visibility", RadarEventDurations]
when_omitted:
  kind: value
  value: ""
  note: The list stays empty and an event's own kind is used to index it anyway, dereferencing a null pointer.
---

Entries are positional: one per [radar event](/reference/enums/radar-event/) kind, in the order that page lists them, and an event indexes the list with its own kind. The timer is loaded on the frame the box stops turning and covers only the settled marker; the sweep inward is drawn whatever this list says. Entries are game frames, 900 to the game minute.

Expiry does not retire the event. It stops updating and stops being drawn, but it stays in play — and in the scan that [`RadarEventSuppressionDistances`](/keys/radareventsuppressiondistances/) drives — until [`RadarEventDurations`](/keys/radareventdurations/) runs out too. When the duration is the shorter of the two the event is deleted first and the rest of this timer never shows, so the marker is drawn for whichever of the two is smaller.

:::danger[The list must carry an entry for all six kinds]
The lookup applies no bounds check, and any of the six kinds can index this list — three are raised by the engine, the other three only by the Radar Event trigger action — so it needs six entries. Entries past the end give whatever integer happens to sit there, so the marker of an uncovered kind either vanishes on the frame it settles or holds until its duration deletes it; a list left empty dereferences a null pointer.
:::

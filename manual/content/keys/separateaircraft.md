---
key: SeparateAircraft
summary: Stops a helipad coming with a free aircraft and pricing itself around one.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "no"
---

Two things are switched off together. The structure that the first [`PadAircraft`](/keys/padaircraft/) entry docks at no longer strips the average price of the first two entries out of its repair figure, so it is repaired against the plain [`Cost=`](/keys/cost/#scope-aircrafttype) written for it — what it costs to buy and what selling it refunds were the written figure either way; and a [`HoverPad=yes`](/keys/hoverpad/) structure no longer receives a free aircraft as it opens. Nothing else changes: aircraft are still built at pads and still dock at them, and are now paid for one at a time.

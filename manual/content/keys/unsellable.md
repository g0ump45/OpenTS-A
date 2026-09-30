---
key: Unsellable
summary: Prevents the BuildingType from being sold.
see_also: ["system:walls-and-gates"]
when_omitted:
  kind: value
  value: "no"
---

The demolish test rejects the type outright, before it looks at buildup artwork or at the structure's current mission, so no instance of it can be sold by hand: the sell cursor tests this before it offers a sale. The routines the engine uses to sell a building on its own behalf — the computer's emergency base sell-off among them — reach the sale directly and never consult the flag.

The flag reaches walls through a second path. Selling a wall cell searches the rules for the first BuildingType whose [`ToOverlay`](/keys/tooverlay/) is that overlay and refuses the sale when that one type is unsellable — the search stops at the first match, so when several BuildingTypes lay the same overlay, only the earliest declared one decides whether the overlay can be sold.

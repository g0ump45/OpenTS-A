---
key: Cost
summary: The credit price of one object of this type, or the multiplier a country or a difficulty applies to every price it pays.
---

An object's price is the figure nearly every credit amount in the game is worked out from: what a factory charges, what a sale refunds, what one step of repair costs, the score a kill adds, the experience it awards, and how much resentment damaging it earns its attacker. [`Points=`](/keys/points/) governs none of these.

## What a structure gives away

A structure that comes with something else has that thing's price taken out of its own to make a second, lower figure:

- a [`FreeUnit=`](/keys/freeunit/) grant deducts that unit's own price, and the result is held at `0` rather than allowed to go negative;
- the structure named as the first [`Dock=`](/keys/dock/) target of the first [`PadAircraft=`](/keys/padaircraft/) entry deducts half the sum of the first two entries' prices, unless [`SeparateAircraft=yes`](/keys/separateaircraft/).

Almost nothing uses that lower figure. The price asked for the structure adds both deductions straight back, so what a factory charges, what a sale refunds, and what a kill is worth in score and experience all come to the written number. A refinery written at `2000` that hands over a `1400` harvester is still bought, sold and killed as a `2000` structure.

The lower figure reaches two things. It prices a step of [repair](/systems/repair/), which is the only place a player sees it, so a structure that comes with something else is cheaper to repair than its written price implies. And it is the figure the test for handing over the free unit compares the price paid against, which [`FreeUnit=`](/keys/freeunit/) covers.

Where the deduction would take the figure below nothing it stops at nothing, and the price then adds back only what was given away — so a structure priced at or under the unit it hands out is worth that unit's price rather than its own.

## What a house pays

The two fractional forms of this key are multipliers rather than prices. A [country](/keys/cost/#scope-housetype) carries one and a [difficulty](/keys/cost/#scope-difficulty-settings) carries another, both starting at `1`, and a house multiplies the price by:

- **In a skirmish or a multiplayer match**, its country's multiplier and its difficulty's together.
- **In a single-player campaign**, its difficulty's alone. The country's is not consulted at all, so a country priced above or below par plays a campaign at par.

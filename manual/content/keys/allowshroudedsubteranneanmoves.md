---
key: AllowShroudedSubteranneanMoves
summary: Whether a subterranean unit accepts a click on an object standing under the shroud.
see_also: ["system:map-visibility", MoveToShroud]
when_omitted:
  kind: value
  value: "no"
---

At the default a move click that would send a subterranean unit — one whose type takes the [`Subterannean` movement zone](/reference/enums/movement-zone/) — onto a shrouded object is swallowed: the click is consumed and no mission is assigned, so the unit stands still. Setting the key to `yes` lets the same click through to the ordinary move handling.

An aircraft is swallowed at the same test and has no equivalent setting. The rule covers a click on an object; a click on shrouded ground is governed by [`MoveToShroud`](/keys/movetoshroud/) instead.

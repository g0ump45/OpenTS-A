---
key: CloseEnough
summary: Distance in cells within which a blocked ground object treats its destination as reached.
see_also: [Stray]
when_omitted:
  kind: value
  value: "2.5"
  note: "640 leptons."
---

The figure is written in cells and multiplied by 256 as it is read, so the stock `2.25` is 576 leptons. It is the tolerance a ground object applies when its route will not go through, and infantry, walkers, hovercraft and driven vehicles all apply it. Two situations reach it.

Where no path can be found at all, an object stops and drops the order. Every kind has to be nearer than this to its destination, and what else it has to clear depends on the kind:

- a driven vehicle or a hovercraft — **All of:** its mission is Move or Guard area, and it is not on a priority mission;
- infantry or a walker — it is not tethered to something.

Where a friendly object is instead sitting temporarily in the way, an object stops rather than telling the obstruction to move aside, under **All of:**

- it is nearer than this to its destination;
- the destination stands less than two terrain levels above or below it;
- it is not standing in a tunnel.

Most of those stopping points carry a fourth term — that the object is not in radio contact — and one of the two hovercraft paths does not, so an object still in radio contact stops there and presses on at the rest.

The same distance settles two further questions. An object beginning a path search to a temporarily blocked cell redirects itself to a passable cell nearby only while it is farther away than this, and an object belonging to a team measures that against [`Stray`](/keys/stray/) instead. And a team counts a member on a move mission as having arrived once it has come within this distance of its destination and stopped moving.

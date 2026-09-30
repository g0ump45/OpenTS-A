---
key: Tunnels
summary: The tile set that supplies the four road tunnel mouths, one per facing.
see_also: [TrackTunnels, DirtTunnels, DirtTrackTunnels, MovementZone]
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is bound to the role.
---

Laying one of these pieces down builds a tunnel. As a cell's terrain is worked out, a cell whose tile reports the [`Tunnel` land type](/reference/enums/land-type/) and that carries no tunnel yet is matched against the four tunnel roles in turn — this one, then [`TrackTunnels`](/keys/tracktunnels/), then [`DirtTunnels`](/keys/dirttunnels/), then [`DirtTrackTunnels`](/keys/dirttracktunnels/) — and the first role whose four pieces contain the tile wins. A tunnel is then created at that cell, entered from the facing the piece's place in the set names: the first piece is entered from the east, the second from the south, the third from the west, the fourth from the north.

The land type comes from the artwork rather than from this key, so a set named here whose tiles do not report `Tunnel` builds nothing at all. What the key settles is which of the four facings each piece of the set stands for.

A tunnel joins the ground on either side of it. Once the cell has tunnel cells on both sides along one axis, the entrance and the exit are registered as a crossing between two otherwise unconnected pieces of ground, and route-finding uses it the way it uses a [bridge](/keys/bridgeset/) span.

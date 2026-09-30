---
key: DirtTrackTunnels
summary: The tile set that supplies the four dirt railway tunnel mouths, one per facing.
see_also: [Tunnels, TrackTunnels, DirtTunnels]
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is bound to the role.
---

The four pieces build a tunnel exactly as the road mouths do, and [`Tunnels`](/keys/tunnels/) covers what that means and how the facing is read off a piece's place in the set. This role is tested last of the four, so a tile that falls inside any of the other three tunnel sets never reaches it.

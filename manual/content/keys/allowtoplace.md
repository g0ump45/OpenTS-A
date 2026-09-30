---
key: AllowToPlace
summary: Parsed tile-set flag that the engine never uses.
no_effect: true
see_also: [RequiredForRMG, TilesInSet]
when_omitted:
  kind: value
  value: "yes"
---

The name promises that a tile set may be offered for placement. The value is read once per tile set and copied onto every tile the set produces, and nothing reads it back. It reaches no placement test, no map generator decision, and not even the multiplayer synchronization checksum, which never visits the isometric tile types at all.

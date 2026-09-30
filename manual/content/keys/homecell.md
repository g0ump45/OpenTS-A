---
key: HomeCell
summary: The waypoint the tactical view opens on and the bookmarks start at.
see_also: [AltHomeCell]
when_omitted:
  kind: value
  value: "98"
---

```ini title="map file"
[Basic]
HomeCell=98
```

Despite the name, the value is a waypoint number rather than a cell number: it selects an entry of the scenario's `[Waypoints]` list, and the cell that entry names is where the view is centered as the map opens. All four view bookmarks are set to the same place, so pressing any of them before recording one returns there. Waypoint `98` is the slot the map editor writes the home position into, which is why most shipped missions name it here.

A waypoint that the scenario never placed is given the middle of the playable area instead, so a map with no home waypoint still opens somewhere sensible. When global flag `0` is set as the mission loads, [`AltHomeCell`](/keys/althomecell/) is used in its place.

:::danger[A waypoint number outside 0 to 100 is written outside the waypoint table]
The table holds waypoints `0` through `100`. The check that decides whether the home waypoint was placed rejects a number outside that range correctly, but the repair that follows then stores the fallback cell at that same out-of-range position, and the view is read back from it. Both accesses land outside the table and corrupt whatever the scenario keeps beside it.
:::

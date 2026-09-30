---
key: Edge
summary: The map edge a scenario's house treats as friendly, used for arrivals and departures.
see_also: [PlayerControl, Credits]
when_omitted:
  kind: value
  value: North
  note: The read substitutes the literal north edge rather than keeping any edge the house already held.
---

The value is one of the [reinforcement sources](/reference/enums/reinforcement-source/), and a value the engine does not recognize stores as no edge at all. Only a campaign mission reads its house records, so this is a campaign setting.

```ini title="scenario map file"
[Nod] ; a house record in the scenario's own house list
Edge=South
```

Three things consult it, all of them about crossing the map boundary rather than about anything inside it.

- A team reinforcement that walks onto the map arrives at the calculated cell on this edge, facing inward. No edge at all is read as north here.
- A unit on the Retreat mission heads for the calculated cell on this edge to leave the map. A unit that belongs to a team measures from the cell the team entered at, and falls back to its own position when that yields nothing.
- A single reinforcement given no mission of its own is sent to the calculated cell on this edge, so that it does not simply stand where it appeared. The flying form of the same delivery arrives from this edge, with anything but the four compass edges treated as north.

The Retreat case has one exception. An aircraft handles that mission itself rather than the way everything else on the map does, and its handling does nothing at all, so an aircraft told to retreat neither picks an edge cell nor leaves: the setting never reaches it.

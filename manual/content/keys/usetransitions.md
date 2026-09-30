---
key: UseTransitions
summary: Lets a generated map's lighting move with the hour instead of holding the hour it was built at.
see_also: [Time, UseIonStorms, Biome]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

With the flag set, generation loads the settings file belonging to the hour named by [`Time`](/keys/time/) — `MORNING.INI`, `DAY.INI`, `DUSK.INI` or `NIGHT.INI` — and takes three things from it: the local scenario settings are read over the map's own, and its trigger types and tag types are registered with the map. Those triggers are what carry the lighting from one hour to the next; the flag by itself schedules nothing.

```ini title="map seed file"
[RandomMap]
Time=1
UseTransitions=yes
```

The flag also changes the floodlights at the start points. Instead of the count the hour would give — none in the morning or afternoon, two at dusk, four at night — every start point is ringed with four, and each light is attached to the tag named `Light On/Off` so that the same triggers can switch them off by day and on again at night.

The generator asks no questions about the Firestorm addon here, so a seed file may set the flag whether or not that addon is present. The map generator dialog offers the flag as a check box, clears it outright when Firestorm is absent, and its randomize button sets it on about half the seeds it produces and only under that addon.

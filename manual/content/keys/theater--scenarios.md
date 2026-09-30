---
key: Theater
scope: scenarios
label: Scenario theater
see_also: [IceGrowthEnabled]
when_omitted:
  kind: value
  value: "TEMPERATE"
---

```ini title="map file"
[Map]
Theater=SNOW
```

The theater is settled before any of the map's contents are read, because it decides which tile, art and palette archives are mounted for the whole load. The name matches one the rules declared under [`[Theaters]`](/formats/rules-registries/), ignoring case; unmodified rules declare `TEMPERATE` and `SNOW`. Beyond the artwork the theater also settles the snow-only behavior in the simulation, so [`IceGrowthEnabled`](/keys/icegrowthenabled/) does nothing in a theater without ice.

Unlike the rest of the scenario's settings, this one lives in the map's `[Map]` section.

A name no theater answers to is reported and the map is played in the first declared theater, as it is when the key is missing altogether.

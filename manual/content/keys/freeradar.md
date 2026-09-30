---
key: FreeRadar
summary: Whether the scenario grants the radar map without a radar structure.
see_also: ["system:power"]
when_omitted:
  kind: value
  value: "no"
---

```ini title="map file"
[Basic]
FreeRadar=yes
```

The search for a working [`Radar=yes`](/keys/radar/) structure is skipped and the radar map is raised on the strength of this setting alone. The other two conditions still apply: an ion storm suppresses the map while it runs, and the local player's house must be producing at least as much power as it draws.

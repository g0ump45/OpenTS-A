---
key: HSBuilding
summary: The BuildingTypes a hunter-seeker drone may walk out of.
see_also: [GDIHunterSeeker, NodHunterSeeker, "system:superweapons"]
when_omitted:
  kind: value
  value: ""
---

Firing a [`Type=HunterSeeker`](/keys/type/) weapon scans every structure the house owns against this list and keeps the *last* match, not the first, so the drone leaves whichever qualifying structure was created most recently. The drone then appears at the nearest cell to that structure that infantry could stand in, and only when that cell lies inside the playable area.

```ini title="rules.ini"
[SpecialWeapons]
HSBuilding=GAPLUG,NATMPL   ; GDI Upgrade Center and Nod Temple of Nod
```

With an empty list, or with a house that owns none of the named types, nothing is created and the discharge spends the charge for nothing.

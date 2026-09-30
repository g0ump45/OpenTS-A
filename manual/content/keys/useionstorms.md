---
key: UseIonStorms
summary: Whether random map generation folds the ion storm file into the map it builds.
see_also: ["system:ion-storms"]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

```ini title="map seed file"
[RandomMap]
UseIonStorms=yes
```

With the option set, generation loads the hard-coded file `ION.INI` and takes three things from it: its `[General]` section is applied over the loaded rules, the six ion values in its `[Lighting]` section replace the ones the generated map would otherwise carry, and its trigger types and tag types are registered with the map. Those triggers are what actually [raises the storms](/systems/ion-storms/#random-maps); the option by itself schedules nothing.

The generator's own randomizer sets the option on about half the seeds it produces, and only while the Firestorm addon is enabled. The map generator dialog exposes it as a checkbox and stores the answer here.

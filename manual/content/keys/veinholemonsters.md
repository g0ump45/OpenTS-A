---
key: VeinholeMonsters
summary: Veinhole monsters the random map generator plants.
see_also: ["system:veins", "VeinholeTypeClass"]
when_omitted:
  kind: unchanged
  note: The read passes the current setting through, and the generator's settings outlive one map, so an omitted assignment keeps whatever the last map built in this session left behind.
---

```ini title="map seed file"
[RandomMap]
VeinholeMonsters=3
```

The figure is held to `0` through `5` only on [the dialog path](/systems/map-generation/#the-dialog-path-and-the-scenario-path), so a larger figure written by hand in a seed file simply asks for more monsters. The generator makes at most 200 placement attempts in total either way, so a crowded map ends up with fewer monsters than asked for rather than holding the generator up; each attempt has to find a five-by-five block of untouched, level, overlay-free ground that also satisfies the [placement test](/systems/veins/#placement). Every monster it plants is given a starting ring of veins around the border of that block.

The pass runs only where the generated map is built in the temperate theater, so a map whose [`Biome`](/keys/biome/) is tundra or taiga is left without monsters whatever the figure says.

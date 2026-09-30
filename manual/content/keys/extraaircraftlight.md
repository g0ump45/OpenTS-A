---
key: ExtraAircraftLight
summary: Extra brightness every aircraft is drawn with, as a fraction of full light.
see_also: [ExtraUnitLight, ExtraInfantryLight]
when_omitted:
  kind: value
  value: "0"
  note: "Any file that declares `[AudioVisual]` re-reads the key and hands the read the stored value divided by full light as whole numbers, so a setting below full light comes back as `0`."
---

```ini title="rules.ini"
[AudioVisual]
ExtraAircraftLight=.2
```

The figure is written as a fraction of full light, where `1` is the full strength the map's own lighting is measured against. An aircraft's brightness starts from the current level lighting scaled by how high it is flying and the brightness of the cell beneath it, and this setting is added on top as a flat amount, the same at every altitude.

It is applied to the aircraft's body voxel. Graphics drawn over the body afterward go through a separate pass that does not take the figure.

:::caution[A later rules file resets this key]
The figure is kept as a whole number of light units, full light being 1000, so the `.2` above is stored as 200. Every later read of the key is handed the stored figure divided by full light as its default, and that division is whole-number: 200 becomes `0`, and `0` multiplied back by full light is stored as `0`. Any later layer that declares `[AudioVisual]` — `langrule.ini`, the Firestorm rules file, or a map, for any key at all — therefore wipes the setting unless it repeats this assignment.
:::

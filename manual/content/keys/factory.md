---
key: Factory
summary: The kind of object the BuildingType produces.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "none"
---

Only `UnitType`, `InfantryType`, `AircraftType` and `BuildingType` make the structure produce for a player; the short names `Unit`, `Infantry`, `Aircraft` and `Building` also parse, and a computer house's building-driven production accepts them, so a structure carrying one produces for the computer but never for a player. The value is matched against the engine's object-kind names without regard to case, and a value the engine does not recognize leaves the type a non-factory.

```ini title="rules.ini"
[MYWEAP] ; example war factory BuildingType
Factory=UnitType
```

The value also picks which of its house's four production slots the structure serves, so two structures naming the same kind share one slot and cannot build two objects at once — what a second one buys is the [multiple-factory speed-up](/systems/production/#more-than-one-factory). [What counts as a factory](/systems/production/#what-counts-as-a-factory) covers the other recognized names, which raise that speed-up without ever producing anything.

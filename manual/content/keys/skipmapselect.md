---
key: SkipMapSelect
summary: Whether the campaign advances straight to a named mission instead of offering the map screen.
see_also: [NextScenario, AltNextScenario, OneTimeOnly, EndOfGame]
when_omitted:
  kind: value
  value: "no"
---

```ini title="map file"
[Basic]
SkipMapSelect=yes
NextScenario=Maps/Missions/GDI2A.MAP
AltNextScenario=Maps/Missions/GDI9C.MAP
```

At the default, winning the mission opens the map selection screen and the player chooses where the campaign goes. Setting the key replaces that choice with the mission's own: the campaign is advanced to [`NextScenario`](/keys/nextscenario/), or to [`AltNextScenario`](/keys/altnextscenario/) when the second global flag is set, and the screen is never shown.

The advance is still a campaign advance, not a direct load. The named map has to be one of the choices the map selection data offers from the mission's current stage, and the stage number moves with it. [`NextScenario`](/keys/nextscenario/) covers what happens when the name is not among them.

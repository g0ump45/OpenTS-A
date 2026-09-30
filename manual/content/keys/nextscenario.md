---
key: NextScenario
summary: The mission the campaign advances to when this one skips the map selection screen.
see_also: [AltNextScenario, SkipMapSelect, OneTimeOnly]
when_omitted:
  kind: unchanged
  note: The stored name is not cleared between missions, so a mission that omits the key keeps whatever the previously loaded mission wrote, and only the first mission of a session finds it empty.
---

```ini title="map file"
[Basic]
SkipMapSelect=yes
NextScenario=Maps/Missions/GDI2A.MAP
```

The name is used only when [`SkipMapSelect`](/keys/skipmapselect/) is set, and only when the second global flag is clear — with it set, [`AltNextScenario`](/keys/altnextscenario/) is taken instead. Nothing else consults it, so a mission that leaves the map selection screen in place can carry any value here without effect.

The advance runs through the campaign's map selection data rather than loading the file directly: the name is compared, ignoring case, against the scenario of each stage the mission's current stage offers as a next step, and a match moves the campaign to that stage. The path written therefore has to be the same path the progression data records, and [campaign progression](/systems/campaign-progression/#campaigns-and-stages) covers where that data lives.

:::caution[An unreachable name sends the player back to the start of the campaign]
A name matching no offered stage shows an error box and drops the player at the campaign's own first mission rather than at the map selection screen. [Choosing the next mission](/systems/campaign-progression/#choosing-the-next-mission) covers why, and which nearby failures reload the mission just won instead.
:::

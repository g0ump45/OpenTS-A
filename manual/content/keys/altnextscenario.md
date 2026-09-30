---
key: AltNextScenario
summary: The mission the campaign advances to instead, when the second global flag is set.
see_also: [NextScenario, SkipMapSelect]
when_omitted:
  kind: unchanged
  note: The stored name is not cleared between missions, so a mission that omits the key keeps whatever the previously loaded mission wrote, and only the first mission of a session finds it empty.
---

```ini title="map file"
[Basic]
SkipMapSelect=yes
NextScenario=Maps/Missions/GDI2A.MAP
AltNextScenario=Maps/Missions/GDI9C.MAP
```

This is the branch a mission takes when the campaign has to fork on something the player did earlier. It is read only where [`NextScenario`](/keys/nextscenario/) would be read — a won mission that sets [`SkipMapSelect`](/keys/skipmapselect/) — and it is chosen over that key whenever global flag `1` is set at the moment the mission is won. The flag is the ordinary trigger-system global, so any trigger that sets it during the mission redirects the advance.

[`NextScenario`](/keys/nextscenario/) covers how the name is resolved against the campaign's progression data and what happens when it matches nothing.

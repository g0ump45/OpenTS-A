---
key: InitialVeteran
summary: Creates the randomly chosen starting units of a skirmish or multiplayer match at elite rank.
see_also: ["system:veterancy", "system:starting-forces"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The flag is read for every scenario but consulted in one place: [the pass that places each house's starting forces](/systems/starting-forces/#spending-the-budget). That pass runs only outside campaign play, so a campaign scenario carrying the setting is unaffected.

```ini title="map file"
[SpecialFlags]
InitialVeteran=yes
```

Only the units and infantry drawn from the random starting selection are promoted. The construction vehicle placed when the match is set up with bases is created separately and stays a rookie.

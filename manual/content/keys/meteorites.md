---
key: Meteorites
summary: Parsed flag that schedules nothing.
no_effect: true
see_also: ["system:tiberium"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The name promises the meteor showers that seed fresh Tiberium as a game runs. The flag is parsed with the rest of the scenario's special options and never consulted; a shower falls only where a trigger action or a superweapon calls for one, whether the flag is set or clear. No gameplay path reads it.

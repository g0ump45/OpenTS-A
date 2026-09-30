---
key: IonStorms
summary: Parsed flag that gates nothing.
no_effect: true
see_also: ["system:ion-storms"]
when_omitted:
  kind: unchanged
  note: The scenario's special options are set up once when the game starts and are not reset between missions, so a campaign mission that omits the key keeps whatever the previously played mission established. Only the first mission of a session finds the initial value, no.
---

The flag is loaded with the rest of the scenario's special flags, but nothing in the game reads it. [Scripted storms](/systems/ion-storms/#starting-a-storm) run in a scenario whether it is set or cleared, and setting it does not make storms occur on their own.

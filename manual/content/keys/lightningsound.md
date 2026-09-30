---
key: LightningSound
summary: Selects the sound played by each ion storm lightning bolt.
see_also: [IonLightningDamage, "system:ion-storms"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
LightningSound=IonThunder ; a sound registered in [SoundList]
```

The sound is played without a position, so a bolt is heard at full volume wherever on the map it lands and wherever the view happens to be. It is played once per bolt, before any damage is applied, and the scripted [Lightning strike at...](/mapping/actions/taction-ion-lightning-strike/) action plays it too.

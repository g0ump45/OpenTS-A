---
key: CloakSound
summary: The sound played at an object's position as it starts to hide or to reappear.
see_also: ["system:cloaking"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
CloakSound=Cloak1 ; a sound registered in [SoundList]
```

The sound is played at the coordinate the object stands on, once at the start of each fade, for every object of every house — including each vehicle and infantryman a growing [cloaking field](/systems/cloaking/#cloaking-fields) passes over, and each structure that fades out under one. One start is silent: when a critically damaged object gives up a cloak part way through, the fade back into view begins without the sound.

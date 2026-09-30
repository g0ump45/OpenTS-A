---
key: GuardSound
summary: Sound acknowledging the guard command.
see_also: [StopSound, ScatterSound, DeploySound]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
GuardSound=GUARDCMD ; a sound ID registered in SOUND.INI
```

The [Guard](/commands/guardobject/) command plays this once after it has walked the selection, at full volume rather than faded from a place on the map. One sound covers the whole selection however many objects were in it.

It is the sound of the key being pressed rather than of an order being taken. The command puts an object into guard area mode only when the player may both move and fire it, so an unarmed object is passed over, but the sound is played whenever the selection holds anything at all. Only an empty selection is silent.

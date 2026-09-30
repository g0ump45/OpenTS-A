---
key: ScatterSound
summary: Sound acknowledging the scatter command.
see_also: [StopSound, GuardSound, DeploySound]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
ScatterSound=SCATCMD ; a sound ID registered in SOUND.INI
```

The [Scatter](/commands/scatterobject/) command plays this once after it has walked the selection, at full volume rather than faded from a place on the map. One sound covers the whole selection however many objects were in it.

It is the sound of the key being pressed rather than of an order being taken. The command only sends its scatter event for an object the player may move, so a structure that does not undeploy into a vehicle is passed over, but the sound is played whenever the selection holds anything at all. Only an empty selection is silent.

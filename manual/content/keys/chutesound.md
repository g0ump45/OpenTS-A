---
key: ChuteSound
summary: Sound of a parachute opening under a passenger dropped from an aircraft.
see_also: [Parachute, Passengers, "system:drop-pods"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
ChuteSound=CHUTE1 ; a sound ID registered in SOUND.INI
```

An aircraft carrying passengers paradrops one of them instead of firing whenever it is told to attack, and this sound is played from the aircraft's position each time one leaves. It is played only after the passenger has been placed successfully: a drop that finds nowhere to put the passenger puts it back aboard in silence. One sound covers one passenger, so a full load is heard as a run of them.

That is the only descent under a parachute the game performs, so the setting covers every one of them. A [drop pod](/systems/drop-pods/) is a separate descent and takes its sound from [`DropPodWeapon`](/keys/droppodweapon/) instead.

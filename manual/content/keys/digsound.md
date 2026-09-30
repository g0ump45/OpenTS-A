---
key: DigSound
summary: Sound of a subterranean unit breaking the surface on its way down or up.
see_also: [Dig, TunnelSpeed, Locomotor]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
DigSound=DIGIN1 ; a sound ID registered in SOUND.INI
```

The sound belongs to the tunnel locomotor, so only a unit that travels underground reaches it, and it is played from the unit's own position three times in a trip. Going down it sounds twice: once as the unit finishes turning toward its destination and tips nose first into the ground, and once again as the dig-in rotation completes and the descent proper begins. Coming up it sounds as the unit rises back through the last fifty leptons to the surface. The [`Dig`](/keys/dig/) animation is raised alongside it on all three.

There is a fourth call, taken when the unit reaches the point it will surface at, but it is guarded by a test for being within fifty leptons of the surface — and the unit is still holding a full cell height below sea level at that moment, so the test never passes and the call never sounds.

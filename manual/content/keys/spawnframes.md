---
key: SpawnFrames
summary: The interval in game frames between a smoke or fire system's particle spawns.
see_also: [BehavesLike, Slowdown, SpawnCutoff, SpawnTranslucencyCutoff, NaturalParticleSystem]
when_omitted:
  kind: value
  value: "1"
---

A system emits on the frames whose number divides by this interval, so a smoke plume set to `10` puts out a particle roughly once every two thirds of a second. Only the `Smoke` and `Fire` behaviors reach it; the rest of the [behaviors](/keys/behaveslike/#scope-particlesystemtype) never consult it.

```ini title="rules.ini"
[MySmokeSys] ; a ParticleSystemType registered in [ParticleSystems]
BehavesLike=Smoke
HoldsWhat=MySmokePuff ; a ParticleType registered in [Particles]
SpawnFrames=10
Slowdown=.0025
SpawnCutoff=15.0
```

A smoke system keeps a working interval of its own that starts here and is stretched by [`Slowdown`](/keys/slowdown/) every frame, so the setting is only the plume's opening rate. Two other settings are read against that stretched interval rather than against this one: [`SpawnCutoff`](/keys/spawncutoff/) retires the system once the interval passes it, and [`SpawnTranslucencyCutoff`](/keys/spawntranslucencycutoff/) starts thinning the new particles. This figure is also the mark the plume's slowing is measured from — a new particle is created `0.35` slower for every frame the working interval has grown past it, with a floor of `2`, so a plume set to `10` and retired at `15` puts out its last particles `1.75` slower than its first.

A fire system holds the interval fixed at this figure — `Slowdown` never reaches it — and emits on one further schedule besides: while its firer has a target and its body is still turning, it also emits every third frame, so a stream thickens as the shooter comes around.

A structure that is knocked to half strength stretches its [`NaturalParticleSystem`](/keys/naturalparticlesystem/)'s working interval by half again on the spot, so the plume immediately thins and reaches its cutoff sooner than an undamaged one would.

:::danger[`SpawnFrames=0` crashes the game]
Both routines divide the frame counter by the interval without checking it first. A `Smoke` or `Fire` system set to zero crashes the game on the first frame one of its systems runs.
:::

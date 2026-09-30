---
key: Lifetime
summary: How many frames a particle system runs before it is retired.
see_also: [BehavesLike, SpawnCutoff, SparkSpawnFrames]
when_omitted:
  kind: value
  value: "-1"
---

The count runs down one a frame from the moment the system appears and is the one retirement condition every [behavior](/keys/behaveslike/#scope-particlesystemtype) shares — the others each carry at most one of their own, and `Gas`, `WeakGas` and `Web` carry none. Reaching the end stops a smoke, fire or railgun system emitting; the particles it already made are left to die in their own time, and the system goes once the last of them has. A spark system is not stopped by it and goes on throwing bursts until its own [`SparkSpawnFrames`](/keys/sparkspawnframes/) run out.

```ini title="rules.ini"
[MyGasPuffSys] ; a ParticleSystemType registered in [ParticleSystems]
BehavesLike=WeakGas
HoldsWhat=MyWeakGas ; a ParticleType registered in [Particles]
Lifetime=3
```

:::caution[Zero and below mean forever, not at once]
The count is tested for exactly zero after each frame's decrement, so a value of `0` steps straight past the test to `-1` and every value below it moves further away. Only a positive figure ever retires a system this way. That is what makes the setting harmless on a smoke or spark type, which has its own way out, and what leaves a gas or web type running for the rest of the scenario.
:::

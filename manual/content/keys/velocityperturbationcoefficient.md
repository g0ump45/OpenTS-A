---
key: VelocityPerturbationCoefficient
summary: How far a railgun particle's speed may run above its own type's velocity.
see_also: [BehavesLike, MovementPerturbationCoefficient, PositionPerturbationCoefficient, Velocity]
when_omitted:
  kind: value
  value: "0.0"
---

The trace carries a running speed offset, which is added to each particle's [`Velocity`](/keys/velocity/) as it is laid. Each step adds a fresh random draw to the offset already in hand and scales the sum by half this figure, so the offset both carries along the beam and stays bounded: neighboring particles differ only a little and the trace ripples along its length rather than jumping about. Only the `Railgun` [behavior](/keys/behaveslike/#scope-particlesystemtype) reads it.

```ini title="rules.ini"
[MyRailgunSys] ; a ParticleSystemType registered in [ParticleSystems]
BehavesLike=Railgun
HoldsWhat=MyRailgunPart ; a ParticleType registered in [Particles]
MovementPerturbationCoefficient=.3
VelocityPerturbationCoefficient=.6
```

This figure is the ceiling on the offset only. Its floor comes from [`MovementPerturbationCoefficient`](/keys/movementperturbationcoefficient/) negated, so the wander is not symmetric unless the two carry the same value. The offset is absolute rather than proportional, and the stock railgun particles travel at well under `1`, so a ceiling of `.6` allows one of them more than twice its type's speed.

At zero the offset stays at zero for the whole trace, and every particle travels at its type's velocity exactly — unless [`MovementPerturbationCoefficient`](/keys/movementperturbationcoefficient/) is itself negative, since the floor is that figure negated and a negative one lifts the offset off zero.

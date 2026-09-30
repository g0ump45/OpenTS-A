---
key: SpiralDeltaPerCoord
summary: How far a railgun trace's corkscrew turns per lepton of beam length, in radians.
see_also: [BehavesLike, SpiralRadius, ParticlesPerCoord, PositionPerturbationCoefficient]
when_omitted:
  kind: value
  value: ".025"
---

Each particle's angle around the beam is its distance from the muzzle multiplied by this figure, so the corkscrew winds at a constant rate however long the shot is. Distance is in leptons, 256 to a cell, and the figure is in radians, which makes `.025` a shade over one full turn per cell and `.035` about one and a half. Only the `Railgun` [behavior](/keys/behaveslike/#scope-particlesystemtype) reads it.

```ini title="rules.ini"
[MyRailgunSys] ; a ParticleSystemType registered in [ParticleSystems]
BehavesLike=Railgun
HoldsWhat=MyRailgunPart ; a ParticleType registered in [Particles]
SpiralDeltaPerCoord=.035
SpiralRadius=6
ParticlesPerCoord=.1
```

The winding rate and [`ParticlesPerCoord`](/keys/particlespercoord/) work against each other: too tight a wind for the density on offer leaves fewer than a handful of particles per turn, and the corkscrew reads as scattered dots rather than a coil. At zero the particles sit in a straight line offset from the beam by [`SpiralRadius`](/keys/spiralradius/) rather than circling it.

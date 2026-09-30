---
key: WebRadius
summary: The radius in cells of the area a web covers.
see_also: [Webby, Particle, WebDuration]
when_omitted:
  kind: value
  value: "2"
---

The figure is whole cells, not leptons. Every cell whose offset from the impact cell falls inside a circle of that radius is covered, which at the built-in `2` is a rounded block of thirteen cells. Each covered cell releases one particle from the warhead's [`Particle`](/keys/particle/) system and hands zero damage to everything standing in it, which is what pins the infantry there.

```ini title="rules.ini"
[MyWebWH] ; example WarheadType
Webby=yes
Particle=MyWebSys ; example ParticleSystemType
WebRadius=3 ; twenty-nine cells
```

At `0` only the impact cell is covered. A negative figure covers nothing at all: no particle is released and no object is touched, and since the blast has already been given over to the web, the shot leaves only its impact animation behind.

Every covered cell is given a particle system of its own, so the cost of a detonation grows with the square of this figure.

The setting is read only while [`Webby=yes`](/keys/webby/) stands in the same section.

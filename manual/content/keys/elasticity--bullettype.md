---
key: Elasticity
scope: bullettype
label: Projectile rebound damping
see_also: [Bouncy, Arcing]
when_omitted:
  kind: value
  value: ".75"
---

The fraction of its speed a projectile keeps when it rebounds off the surface it landed on. The rebound is worked out in the frame of reference of the slope the projectile came down on rather than against flat ground, so a projectile that lands on a ramp is thrown off downhill.

Only a [`Bouncy=yes`](/keys/bouncy/) projectile ever survives long enough to show it. Everything else is forced to detonate on its first landing, with the rebound already computed and discarded.

`0` leaves the projectile motionless on the surface, where the settle check ends it on the following frame. A figure above `1` adds speed on every rebound instead of shedding it.

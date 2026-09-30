---
key: Inaccurate
summary: Scatters the aim point of an arcing shot before its arc is solved.
see_also: [Arcing, BallisticScatter]
when_omitted:
  kind: value
  value: "no"
---

The scatter reaches only a projectile that is also [`Arcing=yes`](/keys/arcing/). The offset from the barrel to the predicted target position is moved in a random direction by between half of [`[CombatDamage] BallisticScatter`](/keys/ballisticscatter/) and all of it — half a cell to a whole cell at the engine default — and the ballistic arc is then solved to that displaced point. The shot therefore falls short, long or wide by that much, and the firer never corrects for it.

```ini title="rules.ini"
[MYARTILLERYSHELL] ; a BulletType, registered by a weapon naming it as its Projectile
Image=120MM
Arcing=yes
Inaccurate=yes
```

Two smaller effects do not need `Arcing`. A projectile that goes off within 32 leptons of its target is normally moved onto the target's center so that the blast is seen to strike it; an inaccurate one is left where it went off. And the anti-armor and anti-infantry ratings the engine works out for an object carrying the weapon are halved; those ratings are consulted only when a newly produced unit is told whether to wait in the middle of its base or out toward the edge.

A shot fired from a platform that is moving is separately marked inaccurate for that one shot, but nothing live reads that per-shot mark. Only the setting on the projectile type is consulted.

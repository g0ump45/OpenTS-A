---
key: ROT
scope: bullettype
label: Projectile rate of turn
when_omitted:
  kind: value
  value: "0"
---

Any figure above zero makes the projectile a homing one, and that is the switch between the engine's two flight models. A homing projectile is flown by the missile autopilot, which steers it toward its target and lifts it over terrain in the way; everything else follows the arc it was launched along until it hits something.

The figure is not applied flat. It is swung upward from itself by [`MissileROTVar`](/keys/missilerotvar/) over a fifteen-frame cycle, running between the written figure and one plus twice that share of it — never below it — with the projectile's own identifier mixed into the phase so that missiles fired together do not all weave in unison, and it is raised by half over the last cell of the approach so a target that dodges at the last moment can still be caught.

Homing changes the launch as well. The shot leaves along the firer's turret facing rather than pointing at the target, and it takes the weapon's [`Speed=`](/keys/speed/#scope-weapontype) as written instead of having that speed recomputed from the weapon's range. Three figures are special-cased for aircraft: at `ROT=0` the shot takes the aircraft's own apparent speed and turret yaw; at `ROT=1` the aircraft aims the shot straight at its target and gives it the primary weapon's speed, and only a projectile at `ROT=1` or below is considered suited to a strafing run.

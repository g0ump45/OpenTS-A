---
key: DeployToFire
summary: Makes a vehicle deploy before it may shoot, and stops a player's copy picking targets for itself.
see_also: ["DeploysInto", "NoMovingFire", "Buildable"]
when_omitted:
  kind: value
  value: "no"
---

The flag ties firing to ground the vehicle could deploy on. A cell qualifies when it carries no ramp, holds no building, and belongs to a land type whose [`Buildable`](/keys/buildable/) entry is set. Standing anywhere else, the vehicle answers a request it would otherwise grant with a demand to deploy first.

Given a target it can otherwise hit, the vehicle deploys rather than shooting: the deploy order is issued in place of the shot, whether the weapon was clear to fire or merely needed to turn.

```ini title="rules.ini"
[MYSIEGETANK] ; a UnitType registered in [VehicleTypes]
DeployToFire=yes
DeploysInto=MYSIEGEGUN ; a BuildingType registered in [BuildingTypes]
```

A vehicle looking for somewhere to shoot from restricts its search to deployable ground whenever the cell it currently stands on is not deployable, and narrows the range it will search to two cells beyond its distance from the target so it settles close rather than wandering to the edge of its reach.

Under a human player the flag also switches off target acquisition entirely: such a vehicle never chooses a target of its own and only ever shoots what it is ordered to. A computer-controlled one keeps its ordinary target search. That restriction belongs to the flag alone — a vehicle that deploys before firing only because its [`DeploysInto`](/keys/deploysinto/) structure is a [`TickTank=yes`](/keys/ticktank/) one still picks its own targets.

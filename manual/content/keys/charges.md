---
key: Charges
summary: Makes a structure wind its turret animation up to full charge before the weapon will fire.
see_also: ["TurretAnim", "TurretChargeAnimRate", "TurretAnimIsExclusive", "IsLaser"]
when_omitted:
  kind: value
  value: "no"
---

The flag is consulted on structures only, and only in the first weapon slot. A structure holding a charging weapon there refuses every shot until it is charged, so the wind-up sits in front of the shot rather than behind it as a reload would.

Charging begins once the structure has a target, its house has full power and the structure is switched on, and it is barred while the structure is still building itself. [`TurretChargeAnimRate`](/keys/turretchargeanimrate/) covers the pace of the wind-up and the frame it completes at. Losing the target, dropping below full power or switching the structure off discharges it, and the wind-up starts again from nothing when the conditions return.

Firing does not always spend the charge. Only an [`IsLaser=yes`](/keys/islaser/) weapon discharges the turret, and only when the structure is down to its last round — which an [`Ammo`](/keys/ammo/) left unset counts as, since an unlimited pool is stored as a count below zero. A structure with a stock of rounds keeps its charge until the last of them, and a charging weapon that draws no laser never discharges by firing at all: it winds up once and then pays only [`ROF`](/keys/rof/) between shots for as long as it holds its target.

```ini title="rules.ini"
[MyObelisk] ; example WeaponType
Charges=yes
IsLaser=yes
ROF=120
```

The flag has no effect on a vehicle, an infantry or an aircraft. Such an object fires the weapon at once and pays only its ordinary reload.

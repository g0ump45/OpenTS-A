---
key: Jellyfish
summary: Replaces a vehicle's whole firing behavior with an automatic sting on everything in the cells around it.
see_also: ["Primary", "IsLimpetDrone", "NonVehicle"]
when_omitted:
  kind: value
  value: "no"
---

A vehicle carrying the flag never runs the ordinary firing logic and never approaches a target, though it may still hold one and turn toward it in the normal sense. In its place a sting runs on its own schedule: on every eighth frame of its animation it sweeps the three-by-three block of cells centered on itself.

```ini title="rules.ini"
[MYJELLY] ; a UnitType registered in [VehicleTypes]
Jellyfish=yes
NonVehicle=yes
Primary=MYSTING ; a WeaponType; only its Damage, its warhead and its Report are read
```

Each cell of that block is taken only when its ground stands within 384 leptons of the jellyfish's own height — a cell is 256 — and every object standing there is then examined. An object is stung under **All of:**

- it is infantry, a vehicle, an aircraft or a structure, and it has strength left;
- it is not the jellyfish itself;
- it is not a visceroid;
- it is not an [`InvisibleInGame=yes`](/keys/invisibleingame/) structure;
- it is not an ally.

The damage is the [`Primary`](/keys/primary/) weapon's [`Damage`](/keys/damage/) scaled by that weapon's warhead entry for the target's armor, applied directly and credited to the jellyfish. No projectile is created and no distance falloff applies, so the whole block takes the full figure. Once anything in the sweep has been hit the weapon's [`Report`](/keys/report/) sound is played again for every cell still to be examined.

Movement is loosened to match. The jellyfish does not treat an allied object standing in its way as a temporary blockage and does not treat a cell reserved by another object heading into it as blocked, so it drifts through traffic that would stop an ordinary vehicle. It is drawn from a single frame counter with no facing frames, sorted deeper by its own world height, and an explosion whose center is above ground level sweeps it in along with aircraft and jumpjet infantry.

---
key: Parachute
summary: The canopy drawn above a paradropped passenger on the way down.
see_also: [BombParachute, ChuteSound, "system:drop-pods"]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
Parachute=MYCHUTE ; an AnimType registered in [Animations]
```

An aircraft carrying passengers drops them instead of firing its weapon. Each passenger is placed at the aircraft's own center, marked as falling, and given one of these animations attached to it, so the canopy tracks the passenger down and is released when it lands. A passenger the ground will not take is put back into the hold and hidden instead, and no canopy is created.

Every passenger takes this canopy. [`BombParachute`](/keys/bombparachute/) sits behind a branch that nothing can reach.

Nothing about the descent belongs to the animation: the fall rate, the landing and the mission the passenger takes up on arrival are all fixed elsewhere. Only the artwork is this setting's.

:::danger[An unset animation crashes the game at the first paradrop]
The canopy is created without first checking that one was named, so with the key unset the game crashes the first time a loaded aircraft is ordered to attack.
:::

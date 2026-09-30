---
key: SmallFire
summary: The lesser of the two flames the engine lights for itself.
see_also: [LargeFire, OnFire, Sparky, Flamer, Scorch]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
SmallFire=MYFIRE_SM ; an AnimType registered in [Animations]
```

Three paths create it, none of them nameable from an object type:

- A [`Flamer=yes`](/keys/flamer/) animation lays a patch of fire around itself when it reaches its middle frame: one of these a quarter of a cell out in a random direction, another on an even chance five eighths of a cell out, and a [`LargeFire`](/keys/largefire/) on a further even chance. Each is placed at the nearest free spot to the point picked.
- A [`Scorch=yes`](/keys/scorch/) animation below ten leptons creates one at its own center, unless it is standing on water, beach, ice or rock. If the animation was attached to an object, the flame is attached to it too.
- Every cell of a structure being torn down has an even chance of one, half a cell out in a random direction, and half of those also get a `LargeFire`.

A structure knocked down a damage level uses it as well. [`Sparky`](/keys/sparky/) covers that case, including the engineer that suppresses it and the [`OnFire`](/keys/onfire/) set that replaces it.

:::danger[An unset animation crashes the game at the first flame]
Every one of these paths creates the animation without first checking that one was named. An ordinary structure taking damage reaches it, so leaving the key unset crashes the game within the first few exchanges of fire.
:::

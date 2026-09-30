---
key: LargeFire
summary: The greater of the two flames the engine lights for itself.
see_also: [SmallFire, OnFire, Flamer, Sparky]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
LargeFire=MYFIRE_LG ; an AnimType registered in [Animations]
```

Two paths create it, and both pair it with [`SmallFire`](/keys/smallfire/) rather than using it alone:

- A [`Flamer=yes`](/keys/flamer/) animation reaching its middle frame lays one on an even chance, a little under half a cell out in a random direction from its center and snapped to the nearest free spot, alongside the small flames it always lays.
- A structure being torn down works over every cell of its footprint; a cell that draws a small flame has a further even chance of one of these on top, a quarter of a cell out in a random direction.

Neither path is nameable from an object type, so this is the only place the effect can be changed. A structure knocked down a damage level short of destruction never reaches it: [`Sparky`](/keys/sparky/) covers that case, where the choice is between the small flame and the [`OnFire`](/keys/onfire/) set.

:::danger[An unset animation crashes the game at the first structure destroyed]
Both paths create the animation without first checking that one was named, so leaving the key unset crashes the game as soon as any structure comes down.
:::

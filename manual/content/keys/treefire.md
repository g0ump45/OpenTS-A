---
key: TreeFire
summary: The two flames that burn on a terrain object once it catches.
see_also: [Sparky, Wood, Immune, TreeFlammability, OnFire]
when_omitted:
  kind: value
  value: ""
---

```ini title="rules.ini"
[AudioVisual]
TreeFire=MYTREEFIRE1,MYTREEFIRE2 ; AnimTypes registered in [Animations]
```

A terrain object catches fire only if it is not already burning, is not crumbling, carries [`Armor=wood`](/keys/armor/) and is not a Tiberium spawner. [`Sparky`](/keys/sparky/) covers the warhead side of that — a [`Wood=yes`](/keys/wood/) warhead against an [`Immune=no`](/keys/immune/) terrain type — and [`TreeFlammability`](/keys/treeflammability/) covers a fire spreading from one object to the next.

The flame is placed 80 leptons above the object's center, attached to it so it follows the sprite, and given 255 repetitions of the animation's own loop count so that it burns until the object puts it out rather than running to an end of its own.

Only two slots are ever used. The choice between them is even and carries no meaning of its own, so naming a small flame first and a large one second does not make small fires more common — the object simply shows one or the other. Entries past the second are unreachable.

:::danger[Fewer than two entries can crash the game when an object catches fire]
Nothing checks how many entries the list holds before slot 0 or slot 1 is taken. With one entry, half of all fires read the slot after the end of the list and hand whatever is there to the animation system, so the game either crashes or draws something arbitrary; with an empty list it is every fire.
:::

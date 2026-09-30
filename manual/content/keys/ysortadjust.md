---
key: YSortAdjust
summary: Biases where the animation falls in the ground layer's drawing order, in leptons.
see_also: ["YDrawOffset", "Surface", "ActiveAnimYSort", "MoveFlash"]
when_omitted:
  kind: value
  value: "0"
---

The figure is copied onto each animation of the type as it is created and added to the sorting position that decides the order the ground layer is drawn in, of which a cell is 256 leptons. A negative figure sorts the animation earlier and so puts it behind the objects it shares the layer with; a positive one puts it in front.

It moves nothing on screen. The artwork is drawn in the same place either way, and only what covers what changes. [`YDrawOffset`](/keys/ydrawoffset/) is the setting that moves the sprite.

The ground layer is the only layer kept in order, so the figure does nothing on an animation that is neither [`Surface=yes`](/keys/surface/) nor pinned to an object.

An animation a structure runs in one of its slots is given the slot's own figure instead of this one, including the zero the slot holds when it states nothing. [Placement and draw order](/systems/building-animations/#placement-and-draw-order) covers that override and the byte the slot's figure has to fit in.

:::caution[The move flash animation loses its figure in multiplayer]
The animation named by [`MoveFlash=`](/keys/moveflash/) has its figure overwritten with -5000 the first time a move order is given in a network game, and keeps that value for the rest of the session. Whatever the type states is discarded there; a campaign and a skirmish leave it alone.
:::

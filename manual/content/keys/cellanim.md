---
key: CellAnim
summary: Animation created on a cell when this overlay is laid on it.
see_also: ["system:tiberium", Overrides, Tiberium]
when_omitted:
  kind: value
  value: none
---

An animation of the named type is created for the cell each time an overlay of the type is laid down, placed at ground level. Where the cell already grows Tiberium, that animation is switched to the Tiberium's color scheme and takes the cell's own brightness, so an effect placed this way tints with the crop it belongs to.

```ini title="rules.ini"
[MYCRYSTAL]           ; example Tiberium overlay
Tiberium=yes
CellAnim=MYSPARKLE    ; example AnimType registered in rules.ini
```

The animation is created whether or not the overlay was actually accepted onto the cell — a placement refused by [`Overrides`](/keys/overrides/) on the overlay already there still produces one.

The setting also stands in for the overlay's own artwork in three places:

- an overlay named by a map's overlay pack is created when it has artwork **or** an animation named here, so an artless type can still be placed from a map;
- the radar and map-preview color comes from the animation's artwork — for an ordinary overlay only when it has no shape of its own, and for a Tiberium overlay whether or not it has one;
- a Tiberium overlay held on the cursor for placement draws the animation's artwork when the growth variety it would show has no shape.

An animation flagged as animated Tiberium checks each frame that the overlay beneath it still names it here, and marks itself for deletion the moment that stops being true — which is how such an effect goes away with the crop.

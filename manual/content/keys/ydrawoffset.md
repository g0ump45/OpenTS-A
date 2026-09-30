---
key: YDrawOffset
summary: Shifts the animation's artwork down the screen, in pixels, as it is drawn.
see_also: ["YSortAdjust", "Tiled", "ActiveAnimY"]
when_omitted:
  kind: value
  value: "0"
---

The figure moves the sprite itself: a positive number pushes the artwork down the screen and a negative number lifts it. It is the way to bring a shape whose art is not centered on its logical position into place without touching the shape file.

Every path the animation is drawn through applies it — the ordinary draw, the flat-on-the-ground draw, each copy of a [`Tiled=yes`](/keys/tiled/) animation, the shadow under a bouncing one, and the second pass drawn under a burning victim.

The same figure is added to the depth the animation's pixels are written at, which cancels the shift rather than compounding it: the artwork moves down the screen but keeps the depth of the position the animation was asked to draw at, so nudging a sprite into place does not change what covers it.

This is the setting that moves the animation. [`YSortAdjust`](/keys/ysortadjust/) moves nothing and only changes what the animation is drawn in front of.

The stand-in a structure's animation leaves behind under the fog of war is drawn without the offset, so an animation carrying a large one jumps by that many pixels the moment the fog closes over its structure and jumps back when the fog lifts.

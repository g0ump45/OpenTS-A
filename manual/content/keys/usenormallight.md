---
key: UseNormalLight
summary: Draws the animation at full brightness instead of at the light level where it stands.
see_also: ["ShouldUseCellDrawer", "AltPalette"]
when_omitted:
  kind: value
  value: "no"
---

With the flag off, the animation is drawn at the brightness of whatever it belongs to: the tile brightness of its cell for a veinhole tendril or an animation belonging to the ground, and the cell's brightness for an ordinary animation. Under an ion storm, in the dark or beside a light source, the animation dims and brightens along with the ground. An animation that has been handed a palette of its own takes the brightness handed with it — a structure's own brightness for one it runs, the brightness of the cell it landed in for a piece of tiberium debris, and the neutral level for a burning victim, which is given no brightness at all.

With it on, none of that is read and the animation is drawn at the neutral level. An explosion, a muzzle flash or a fireball wants it, since those light the ground rather than being lit by it, and a dark cell would otherwise swallow them.

The flag changes brightness only. Which palette the animation is remapped through is a separate decision, made by [`ShouldUseCellDrawer`](/keys/shouldusecelldrawer/) and [`AltPalette`](/keys/altpalette/).

The stand-in a structure's animation leaves behind under the fog of war makes the same test. The shadow drawn beneath a bouncing animation is drawn at the neutral level whatever the flag says.

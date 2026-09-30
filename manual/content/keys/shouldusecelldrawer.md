---
key: ShouldUseCellDrawer
summary: Draws a structure's animation in the colors and at the brightness of the structure it belongs to.
see_also: ["ActiveAnim", "AltPalette", "UseNormalLight"]
when_omitted:
  kind: value
  value: "yes"
---

Only an animation a structure runs in one of its animation slots reads the flag. As the slot is filled, and again whenever the structure's appearance is brought back in line after a lighting or ownership change, the animation is handed the owning house's color scheme and the structure's own brightness to draw with. The stand-in the structure leaves behind under the fog of war makes the same choice.

With `no`, the animation is left with the shared animation palette — or with the first declared color scheme, if it also carries [`AltPalette=yes`](/keys/altpalette/) — and is lit by the ground it stands on instead of by the structure. A fireball or a light bloom that should look the same for every house wants this; a chimney's smoke that should carry the owner's color does not.

Despite the name, no other animation reaches the flag. An animation belonging to the terrain tile it stands on already draws through the same tinted terrain palette as the ground beneath it, and does so whatever this is set to.

```ini title="art.ini"
[MYREFN_B] ; a refinery's fire ball, the same color for every house
Image=MYREFN_B
LoopCount=-1
Rate=350
Surface=yes
ShouldUseCellDrawer=false
UseNormalLight=yes
```

---
key: DamageRadius
scope: animtype
label: Animation strike reach
see_also: ["Damage", "Warhead", "Elasticity", "BounceAnim"]
when_omitted:
  kind: value
  value: "0"
---

A whole number of leptons, 256 to a cell. On the frame a thrown animation strikes something, each object occupying the cell it struck is measured against this reach, and one that falls inside it takes [`Damage`](/keys/damage/#scope-animtype) through the animation's [`Warhead`](/keys/warhead/#scope-animtype).

The distance compared is the sum of the two horizontal separations rather than the straight line between them, so the reach is a diamond and not a circle, and `0` reaches only an object centered exactly on the point of impact. Height is not part of the comparison at all. Only occupants of the one cell struck are examined, so a reach wider than a cell still cannot touch anything standing next door. The armor and distance reduction is worked out on a copy of the damage figure, so the type's stored `Damage` is left as the rules set it and every later animation of the type starts from the same number.

Reaching this path at all takes a contact the physics report as a strike rather than as settling, which [`Elasticity`](/keys/elasticity/#scope-animtype) decides and which an ordinary landing by a shipped bouncing animation does not produce.

The blast at the end of the animation's life is a separate matter: it reaches every object in the impact cell and the eight around it, with the warhead's own [`Spread`](/keys/spread/#scope-warheadtype) deciding how the damage falls off across them, and it does not consult this setting at all.

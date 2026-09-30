---
key: ExitCoord
summary: The offset a barracks measures a produced object's starting position by.
see_also: [GDIBarracks, NODBarracks, WeaponsFactory, "system:production"]
when_omitted:
  kind: value
  value: 0,0,0
---

```ini title="rules.ini"
[GAPILE] ; the stock GDI barracks
GDIBarracks=yes
ExitCoord=-64,64,0
```

The three components are a raw lepton count rather than a distance in cells — 256 leptons to the cell, so the stock figures above shift the soldier a quarter of a cell back along one axis and a quarter of a cell on along the other. They are added to the center of the cell the object is placed on. The third is an absolute height rather than a height above that cell, and an object that would end up beneath the terrain is lifted back onto it, so a figure at or below the local ground level leaves it standing on the ground.

Only a barracks reaches them. A [`GDIBarracks=yes`](/keys/gdibarracks/) structure prefers the cell one along and two down from the top-left cell of its footprint as the object's destination, and a [`NODBarracks=yes`](/keys/nodbarracks/) structure two along and two down; the offset is applied only when that preferred cell is the one picked. The object is not placed on it. The cell it appears in is that preferred cell pulled back inside the footprint on either axis it overruns, so on a footprint two cells deep — which both stock barracks are — the object appears on the bottom row of the building itself, and the offset is measured from the center of that cell. When the preferred cell is blocked and the object leaves from somewhere else around the footprint, the offset is dropped and the object stands in the middle of the pulled-back cell. [Leaving the factory](/systems/production/#leaving-the-factory) covers how the exit cell is picked.

:::caution[A weapons factory never reads it]
A [`WeaponsFactory=yes`](/keys/weaponsfactory/) structure is the only type that asks where its object should appear through the separate exit-coordinate path, and that path answers with a fixed `98,188,0` offset from the structure's own coordinate before it looks at this key. Writing the key on such a type changes nothing.
:::

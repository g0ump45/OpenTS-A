---
key: AmmoCrateDamage
summary: Raw damage of the blast an exploding overlay leaves behind when it is set off.
see_also: ["Explodes", "C4Warhead", "BarrelExplode", "BarrelDebris", "BarrelParticle"]
when_omitted:
  kind: value
  value: "100"
---

An overlay carrying [`Explodes=yes`](/keys/explodes/#scope-overlaytype) is cleared from its cell the moment an explosion reaches it, and this figure is the blast left in its place. The blast is centered on that cell, carries [`C4Warhead`](/keys/c4warhead/), and sets off any chain-reactive growth it touches. It is credited to nobody, so a unit killed by an exploding barrel counts as no one's kill.

[`BarrelExplode`](/keys/barrelexplode/) plays over the blast. One piece of [`BarrelDebris`](/keys/barreldebris/) is thrown — the first entry in that list to pass a fifteen percent roll, and none at all when every entry fails — and [`BarrelParticle`](/keys/barrelparticle/) is spawned on a twenty-five percent roll. Each of the four cells directly north, east, south and west that also holds an exploding overlay is set alight with a fire animation the engine names for itself.

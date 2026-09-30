---
key: Crusher
summary: Lets a vehicle drive over crushable objects and walls instead of being blocked by them.
see_also: ["AutoCrush", "TiltsWhenCrushes", "Crushable", "SpeedType"]
when_omitted:
  kind: value
  value: "no"
---

A vehicle carrying the flag — or one whose crew has earned the crusher ability from [`VeteranAbilities`](/keys/veteranabilities/) — treats a cell holding a [`Crushable=yes`](/keys/crushable/#scope-aircrafttype) object as passable rather than as something to shoot or route around. It is what lets an unarmed vehicle answer a click on enemy infantry with a move order instead of a select, and it lets the pathfinder count a friendly crushable wall as destroyable rather than solid. Driving onto a crushable wall overlay destroys the segment outright, ignoring ownership and damage stage; [Crushing, clearing and selling](/systems/walls-and-gates/#crushing-clearing-and-selling) covers what that does to the wall.

The flag also has one effect that has nothing to do with crushing. A UnitType whose [terrain speed class](/reference/enums/speed-type/) no file has settled yet is given `Track` when the flag is set and `Wheel` when it is not, and a [`SpeedType=`](/keys/speedtype/) in the same section then overrides that. Leaving both keys out therefore costs a crusher against the tracked movement table and a non-crusher against the wheeled one.

Two further settings sit on top of it. The rules-wide crushing thresholds decide whether a vehicle goes looking for something to run over rather than firing at it — [`AutoCrush`](/keys/autocrush/#scope-aircrafttype) on the type itself reaches no live branch — and [`TiltsWhenCrushes`](/keys/tiltswhencrushes/) decides whether the hull lurches while it does.

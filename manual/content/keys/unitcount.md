---
key: UnitCount
summary: Starting figure for the unit count a multiplayer or skirmish match opens with.
see_also: [AllowedToStartInMultiplayer, BaseUnit, Bases, "system:starting-forces"]
when_omitted:
  kind: value
  value: "10"
---

The value seeds the match's unit count as the rules are read, and the setup screen then writes over it. Every setup screen that offers the figure runs its slider from `1` to `10` and hands back what the slider is left showing, so a seed outside that range does not survive a screen that shows it.

The figure is not a number of objects. It is multiplied by the average price of every type [allowed to start](/keys/allowedtostartinmultiplayer/), and each house spends the resulting budget one object at a time. With bases enabled one is taken off the figure first, to pay for the [`BaseUnit`](/keys/baseunit/) each house is placed with. [Starting forces](/systems/starting-forces/#the-budget) owns the average and the order the budget is spent in.

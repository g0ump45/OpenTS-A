---
key: Bases
summary: Starting state of the bases option for a multiplayer or skirmish match.
see_also: [BaseUnit, UnitCount, "system:crates", "system:starting-forces"]
when_omitted:
  kind: value
  value: "yes"
---

The value seeds the match's bases option as the rules are read, and the setup screen then writes over it. With the resulting option on, every house that is not multiplayer-passive is placed with one [`BaseUnit`](/keys/baseunit/) on its start position and its [`UnitCount`](/keys/unitcount/) budget is reduced by one unit's worth to pay for it; with the option off, each house is given only its random starting objects. [Starting forces](/systems/starting-forces/) covers where both are put down.

The same option is consulted twice more, both times when a crate is opened: [a house that has lost its base](/systems/crates/#money-and-free-units) is only handed a replacement base unit while bases are on, and the ordinary random vehicle result refuses to hand out the base unit at all while they are off.

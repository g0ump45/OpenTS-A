---
key: FreeUnit
summary: The UnitType a structure hands its owner when it opens for business.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "none"
---

The unit is created as the structure opens and placed on the cell to its south; when that cell refuses it two nearby searches follow, and a unit that still cannot be placed refunds its own price and is discarded. A placed unit is assigned the harvest mission. A structure that was captured rather than built, or that came with the scenario, hands out nothing.

Whether the owner receives it also depends on what was paid. A computer house always does. A human-controlled house does only when one of two things is true of the structure:

- it carried no purchase price at all, which covers one placed by a trigger rather than produced, and one whose price fell to `0` because the unit is worth at least as much as the structure;
- the price it paid was greater than its own price with the unit's price already deducted.

A factory charges the written price rather than the deducted one, so the second condition holds for any structure that was actually produced and whose unit is worth anything at all. The first covers one that opened without being bought and was not excluded earlier — a structure placed by a trigger during the mission, and one whose price the deduction drove to nothing.

```ini title="rules.ini"
[MYPROC]        ; example refinery BuildingType
Cost=2000       ; already includes MYHARV
FreeUnit=MYHARV ; example harvester UnitType
```

The unit's price sits inside the structure's cost rather than being added to it, but the price asked for the structure adds it straight back. Naming a free unit therefore changes neither what the structure costs to buy nor what selling it refunds nor what destroying it is worth; it lowers the repair bill, and it sets the figure the second condition above compares against. [`Cost=`](/keys/cost/#scope-aircrafttype) sets out the whole of what the deduction reaches.

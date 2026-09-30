---
key: MovementRestrictedTo
summary: Confines a vehicle to cells of one land type, which is how rolling stock is held to the rails.
see_also: ["IsTrain", "Passive", "SpeedType"]
when_omitted:
  kind: value
  value: none
---

Naming a [land type](/reference/enums/land-type/) refuses the vehicle every cell whose land type is not the one named. The test runs before terrain cost, occupancy, walls, gates and everything else weighed when a vehicle asks whether it may enter a cell, so nothing else can grant an exception to it.

```ini title="rules.ini"
[MYRAILCAR] ; a UnitType registered in [VehicleTypes]
MovementRestrictedTo=Railroad
IsTrain=yes
```

Two allowances are built in. A `Tunnel` cell passes the land type test whatever is named, but on a tunnel mouth five or four cells wide by three deep only subtile 2 is accepted, and on one three wide by four or five deep only subtile 6 is — every other subtile of those mouths is refused, which is what keeps a train entering on the portal rather than through the hillside. A cell of the wrong land type is also allowed when it carries a rail bridge overlay and the vehicle is not standing at that cell's own height, so a restricted vehicle may cross a rail bridge over ground it could never drive on.

A value the engine does not recognize resolves to no restriction at all rather than to an error, and the vehicle then travels wherever its [`SpeedType`](/keys/speedtype/) column allows.

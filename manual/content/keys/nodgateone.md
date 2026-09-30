---
key: NodGateOne
summary: The BuildingType that joins a Nod wall running east to west.
see_also: ["system:walls-and-gates", "Gate"]
when_omitted:
  kind: value
  value: none
---

Wall stitching is not a flag on a type. The named type is the one the [connection logic](/systems/walls-and-gates/#connection-frames) accepts as a continuation of a Nod wall — the stock `NAWALL` overlay — and only from the east and the west, so a Nod wall arriving from the north or south stops dead at it. The brick and sandbag walls the GDI pair covers are a separate family; nothing here connects to them.

The same name also lets the type be placed on a Nod wall the house already owns, undamaged or not, which no ordinary wall building may do. The two cells capping its run are updated both when the type is placed and when it is taken off the map — one cell west of its origin and three cells east of it. Those offsets assume a three-cell footprint.

None of that requires [`Gate=yes`](/keys/gate/). The flag supplies the door cycle and the clearing of walls under the footprint at placement; this key supplies the wall connection, and a type may carry either without the other.

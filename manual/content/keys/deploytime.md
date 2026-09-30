---
key: DeployTime
summary: The time in game minutes a door takes to travel from shut to fully open, or back.
see_also: ["system:walls-and-gates", "Gate"]
when_omitted:
  kind: value
  value: "0"
---

A game minute is 900 frames. The same figure is used for opening and for closing, and three door paths spend it:

| Type | Door it times |
| --- | --- |
| A [`Gate=yes`](/keys/gate/) BuildingType | The [gate's own door](/systems/walls-and-gates/#holding-and-closing), whose drawn frame is the door's completion fraction scaled by [`GateStages`](/keys/gatestages/) |
| A [`WeaponsFactory=yes`](/keys/weaponsfactory/) BuildingType | The door sequence run while a finished vehicle leaves |
| A transport AircraftType | The door held open while a passenger boards, closed once the transport is full |

An InfantryType stores the value and has no door to spend it on.

A transport UnitType never spends it either. A vehicle carries a door of its own and the loading and unloading paths ask it to close, but nothing anywhere asks it to open, and a close is refused outright on a door that was never opened. The door therefore stands shut from the moment the vehicle is built, and a vehicle transport loads and unloads with no door travel whatever the value says.

At `0` a door reaches its end position on the first pass, which for a gate means it opens and closes instantly and never draws an intermediate frame.

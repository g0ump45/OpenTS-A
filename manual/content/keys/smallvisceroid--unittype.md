---
key: SmallVisceroid
scope: unittype
label: Small visceroid behavior
see_also: ["LargeVisceroid", "AltImage", "NonVehicle", "system:tiberium"]
when_omitted:
  kind: value
  value: "no"
---

The flag puts the vehicle on the creature's conduct instead of a vehicle's. Standing still on a guard or empty mission with no destination and no target, it picks one of the eight directions — keeping the last one two times in three — and steps into that cell when it can enter it. Below [`ConditionYellow`](/keys/conditionyellow/) health it heads instead for Tiberium within a sixteen-cell search radius, and once it is standing on Tiberium it accepts only another Tiberium cell as its next step.

Merging is what separates it from a [`LargeVisceroid=yes`](/keys/largevisceroid/#scope-unittype) type. Standing still, it looks at the eight cells around it from north clockwise and stops at the first that holds another small visceroid; if that one has no destination and no target of its own, it is sent here. Finding a neighbor ends the pass either way, so a visceroid with one beside it neither wanders nor makes for Tiberium that frame. Two small visceroids never block each other's cell, so the one that was sent drives all the way onto this one — and on arrival the visceroid it was sent to is turned into the UnitType named by [`LargeVisceroid`](/keys/largevisceroid/#scope-global-rules) at that type's full strength, while the arriving one deletes itself.

Both visceroid flags carry the same handful of exemptions. [`NonVehicle`](/keys/nonvehicle/) is forced on after this key is read, whatever the section said. An EM pulse passes over the creature without stunning it, and being immobilized does not stop it firing, which no other object may do. It is not required to bring a turret to bear before it shoots, a [`Jellyfish=yes`](/keys/jellyfish/) unit never stings it, and it is drawn without a shadow — from its ordinary artwork while wandering and from [`AltImage`](/keys/altimage/) for the five frames of an attack.

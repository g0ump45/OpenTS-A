---
key: Insignificant
scope: aircrafttype
label: Bookkeeping exemption
see_also: ["system:capture"]
when_omitted:
  kind: context-dependent
  note: An AircraftType, BuildingType, InfantryType, ParticleType, ParticleSystemType or UnitType section starts at no. A BulletType, OverlayType, SmudgeType, TerrainType or VoxelAnimType section starts at yes.
---

Four behaviors read the value, and all of them belong to objects a house owns, so only an AircraftType, a BuildingType, an InfantryType or a UnitType is affected by it:

- The object is skipped when a house adds it to or removes it from its inventory, so it never enters the running count of that type that [`BuildLimit`](/keys/buildlimit/) measures against. An `Insignificant=yes` structure therefore [changes hands](/systems/capture/#what-changes-hands) without moving between the two houses' tallies at all. The separate active-structure count that prerequisites read is not gated this way and does move.
- A structure's destruction is left out of both houses' building loss and kill records and out of the multiplayer statistics. The equivalent records for a vehicle, an aircraft or an infantry are not gated this way.
- A damaged structure raises no base-under-attack announcement, no radar event and no attacked trigger for its owner.
- A computer house sends no defensive detachment when the object is attacked.

Barrels, land mines and the other scenery-like structures are the intended holders. The setting reaches nothing else: it gates no cursor, no mission, no targeting filter and no capture test.

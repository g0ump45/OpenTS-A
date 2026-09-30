---
key: Crushable
scope: aircrafttype
label: Crushable by vehicles
see_also: ["system:walls-and-gates", "CrushSound", "Crusher"]
when_omitted:
  kind: context-dependent
  note: An InfantryType section starts at yes. Every other object type in this scope starts at no.
---

The crusher on the other side of this setting is a [`Crusher=yes`](/keys/crusher/) UnitType, or one carrying the crusher veteran ability. Everything below applies to that pairing only; nothing else in the game destroys the object or overlay over it, though the flag does shape pathfinding and the track a driving vehicle takes.

**An overlay** marked crushable and [`Wall=yes`](/keys/wall/) is destroyed outright the moment such a vehicle drives onto it — a crushable overlay that is not a wall plays the sound and rocks the vehicle but survives: the cell plays the overlay's [`CrushSound`](/keys/crushsound/#scope-aircrafttype), the segment is removed with no regard for its owner or its damage stage, and the vehicle rocks forward. The cell also reports itself as crushable terrain, which lets a crusher's pathfinding route straight through a crushable wall while an allied one is additionally flagged as friendly and destroyable.

**An object** marked crushable is run over rather than shot. A crusher that finds one in the cell it is entering deletes it, plays its `CrushSound`, and records the kill; allied objects are passed over unharmed unless the crusher is a train. A computer-controlled crusher drives at a crushable target inside `[CombatDamage] Crush=` instead of firing on it — [`AutoCrush=yes`](/keys/autocrush/) and `[CombatDamage] PlayerAutoCrush=` are tested only on branches a house a human is playing never reaches — and an unarmed crusher pointed at a crushable object is offered a move cursor in place of the attack cursor it could not use.

---
key: IsTiberium
scope: animtype
label: Animation Tiberium seeding
see_also: ["system:tiberium", "TiberiumSpawnType", "TiberiumSpreadRadius", "Bouncer"]
when_omitted:
  kind: value
  value: "no"
---

Tiberium is planted around the place a thrown animation ends its life on solid ground. The type planted comes from [`TiberiumSpawnType`](/keys/tiberiumspawntype/) and the cells that take it from [`TiberiumSpreadRadius`](/keys/tiberiumspreadradius/), and each cell that germinates is set to one of the first three growth stages at random. An animation that ends in water plants nothing, and neither does one that ends more than about a cell and a half above the ground, a bridge deck included.

Only an animation the physics are carrying reaches this at all — one declaring [`Bouncer=yes`](/keys/bouncer/) or [`IsMeteor=yes`](/keys/ismeteor/#scope-animtype). The flag on any other animation is stored and never acted on.

A cell germinates under **All of:**

- it is inside the playable area;
- it is neither under a bridge nor remembered as having been;
- no living, visible building stands on it;
- no Tiberium-spawning terrain object stands on it;
- its ground can be built on;
- it holds no overlay of any kind;
- it is not on a steep ramp;
- its tile allows Tiberium.

Anything the growth would have covered but cannot use is simply skipped.

The planting is the whole of the effect. Nothing about how the animation itself is drawn changes.

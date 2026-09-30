---
key: CrateRadius
summary: The distance from an opened crate within which its area results reach other objects, in cells.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: "2.5"
  note: Fractions are accepted; the default reaches 640 leptons at 256 leptons to the cell.
---

Several crate results are not confined to the object that opened the crate. Each sweeps the ground layer and applies itself to objects whose center lies strictly nearer to the center of the crate's cell than this distance, the [veterancy result](/systems/veterancy/#promotion-without-kills) among them.

How far a result reaches inside the circle depends on the result. The veterancy and cloaking results test position only: objects belonging to other houses, allied or hostile, are treated exactly like the collector's own, and buildings standing inside the circle are included alongside vehicles and infantry. The armor, firepower, and speed results skip any object whose matching multiplier an earlier crate has already changed, and the speed result reaches only infantry and vehicles — never aircraft, and never buildings.

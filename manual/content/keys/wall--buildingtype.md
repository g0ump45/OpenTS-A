---
key: Wall
scope: buildingtype
label: Wall structure
see_also: ["system:production"]
when_omitted:
  kind: value
  value: "no"
---

A structure of this type is never placed as a structure. On reaching the map it creates one of its [`ToOverlay`](/keys/tooverlay/) overlays on the cell, claims the cell for its house, and deletes itself; a cell that refuses the overlay refuses the placement outright.

The flag is also what applies [`WallBuildSpeedCoefficient`](/keys/wallbuildspeedcoefficient/) to the type's build time, last of everything that shapes it.

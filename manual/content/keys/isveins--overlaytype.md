---
key: IsVeins
scope: overlaytype
label: Vein ground
see_also: ["system:veins", "IsVeinholeMonster"]
when_omitted:
  kind: value
  value: "no"
---

The flag makes the overlay count as vein ground wherever [vein growth](/systems/veins/#what-stops-veins) looks at an overlay. A cell carrying one still accepts veins instead of being blocked by its own overlay; a cell beside one is not blocked by that neighbor either; a thin vein draws its connecting piece as though the neighbor were mature vein; and a monster's disposal strips overlays carrying the flag from the block around it. The placement preview also draws an overlay carrying the flag in the local player's color scheme; the in-map render picks that scheme by catalog position instead.

The flag does not make an overlay behave as veins. Growing, harvesting, withering, and the attack all read the vein overlay by its fixed slot in `[OverlayTypes]`, so an overlay given the flag becomes ground the field will cross without becoming a field itself.

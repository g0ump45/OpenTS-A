---
key: SpecialZOverlay
summary: Parsed shape name that the engine never draws.
no_effect: true
see_also: ["SpecialZOverlayZAdjust"]
when_omitted:
  kind: value
  value: ""
---

The value names a shape file without its extension. A non-empty one is loaded as the structure's artwork is fetched, through the same theater name substitution the main image goes through, and kept on the type; no drawing path reads it afterward. A name matching no file in the mix archives leaves the type holding nothing, and changes nothing either way.

The depth a structure writes for other objects to sort against comes from `BUILDNGZ.SHP`, one shape shared by every BuildingType that no key replaces. A structure six or more cells wide is drawn without any depth shape at all, and so is a gate part way through opening or closing.

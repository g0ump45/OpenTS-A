---
key: Supress
summary: Discounts a candidate target that stands near buildings allied to the firing object.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "no"
---

The check runs only while candidates are being scored, and only for the weapon in the firing object's first slot. Each allied building found in the cell rings around a candidate halves that candidate's threat score, so a candidate hemmed in by friendly structures falls behind an equally attractive one standing in the open.

The rings searched come from [`FireSupress`](/keys/firesupress/) in `[CombatDamage]`, whose default of one cell leaves no ring to walk: the discount never applies until that distance is raised.

The setting neither stops the weapon firing nor changes the damage it deals. It only makes the object less likely to choose such a target for itself.

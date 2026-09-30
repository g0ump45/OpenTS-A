---
key: Technician
summary: The InfantryType that leaves a civilian object, and occasionally an armed one, in place of the ordinary crew.
see_also: ["system:capture", Crew, Crewed]
when_omitted:
  kind: value
  value: none
---

An object whose owning house belongs to no side yields this type for every survivor it produces. An object whose house does belong to a side yields it on a 15% roll, and only while the object carries a primary weapon. Both tests are on the object producing the survivor rather than on the survivor, and both are taken afresh for each one. Everything else falls to [`Crew`](/keys/crew/), and the one-in-four `[General]` [`Engineer`](/keys/engineer/#scope-global-rules) roll an uncaptured building-producing structure takes runs ahead of both.

The flag the label rides on does a little more than label: it also bars the soldier from being picked up as a civilian evacuee and leaves it out of its house's infantry tally. A structure's survivor is displayed under the engine's "Technician" string whenever its own type is [`Nominal=yes`](/keys/nominal/), whichever of the three types produced it; a sold structure marks every survivor that way and a destroyed one only while it has build-up artwork. A vehicle's escaping crew is never marked.

:::danger[Leaving this unset can end a sale]
The value starts as no type at all, and the survivor loop a sale runs reads each pick before testing it for nothing. An armed [`Crewed=yes`](/keys/crewed/) structure reaches this type on 15% of its survivors, and one owned by a house that belongs to no side reaches it on every one.
:::

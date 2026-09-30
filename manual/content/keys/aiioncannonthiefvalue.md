---
key: AIIonCannonThiefValue
summary: The ion cannon rating a computer house gives an enemy vehicle thief.
see_also: [IonCannonDamage, "system:superweapons"]
when_omitted:
  kind: value
  value: ""
---

The rating covers a [`VehicleThief=yes`](/keys/vehiclethief/) InfantryType that is not also an engineer; any other infantry is rated a flat 2. Like every list in this family it is read at the firing house's own difficulty slot, and must carry one entry each for easy, normal and hard; a missing or short list is read past its end. The rating is consulted only while [the target's strength is at or below `IonCannonDamage`](/systems/superweapons/#the-computers-use) — a thief above that figure is left at 1.

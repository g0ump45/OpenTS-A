---
key: AIIonCannonPowerValue
summary: The ion cannon rating a computer house gives an enemy structure that produces more power than it draws.
see_also: [IonCannonDamage, "system:superweapons"]
when_omitted:
  kind: value
  value: ""
---

The test is on the type's rated output against its rated drain, not on the house's balance, so any structure with a net positive [`Power=`](/keys/power/) is rated here — and a structure that also builds something is caught by the two factory tests first. Like every list in this family it is read at the firing house's own difficulty slot, and must carry one entry each for easy, normal and hard; a missing or short list is read past its end. The rating is consulted only while [the target's strength is at or below `IonCannonDamage`](/systems/superweapons/#the-computers-use) — a structure above that figure keeps the flat structure rating of 3.

---
key: AIIonCannonWarFactoryValue
summary: The ion cannon rating a computer house gives an enemy structure that produces vehicles.
see_also: [IonCannonDamage, "system:superweapons"]
when_omitted:
  kind: value
  value: ""
---

The rating covers a [`Factory=UnitType`](/keys/factory/) structure and is the second of the seven structure tests, so it wins over every test below it — a war factory that is also a base defense is rated here. Like every list in this family it is read at the firing house's own difficulty slot, and must carry one entry each for easy, normal and hard; a missing or short list is read past its end. The rating is consulted only while [the target's strength is at or below `IonCannonDamage`](/systems/superweapons/#the-computers-use) — a structure above that figure keeps the flat structure rating of 3.

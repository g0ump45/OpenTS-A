---
key: AIIonCannonHelipadValue
summary: The ion cannon rating a computer house gives an enemy HoverPad structure.
see_also: [IonCannonDamage, "system:superweapons"]
when_omitted:
  kind: value
  value: ""
---

The rating is the last of the seven structure tests; a structure that reaches it and does not carry [`HoverPad=yes`](/keys/hoverpad/) falls through to a flat 4. Like every list in this family it is read at the firing house's own difficulty slot, and must carry one entry each for easy, normal and hard; a missing or short list is read past its end. The rating is consulted only while [the target's strength is at or below `IonCannonDamage`](/systems/superweapons/#the-computers-use) — a structure above that figure keeps the flat structure rating of 3.

---
key: IsTemple
summary: Rates the structure as a temple when a computer house chooses an ion cannon target.
see_also: [AIIonCannonTempleValue, "system:superweapons"]
when_omitted:
  kind: value
  value: "no"
---

One test reads the flag: [the rating a computer house gives each candidate](/systems/superweapons/#the-computers-use) while its ion cannon looks for something worth striking. A flagged structure that reaches the temple test takes [`AIIonCannonTempleValue`](/keys/aiioncannontemplevalue/) in place of the rating an unremarkable structure gets.

Nothing a temple does on the map follows from the flag. The superweapon it grants comes from [`SuperWeapon=`](/keys/superweapon/) and the objects it turns out from [`Factory=`](/keys/factory/); clearing the flag costs it neither.

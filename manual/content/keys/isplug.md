---
key: IsPlug
summary: Rates the structure as an upgrade host when a computer house chooses an ion cannon target.
see_also: [AIIonCannonPlugValue, PowersUpBuilding, "system:superweapons"]
when_omitted:
  kind: value
  value: "no"
---

One test reads the flag: [the rating a computer house gives each candidate](/systems/superweapons/#the-computers-use) while its ion cannon looks for something worth striking. A flagged structure that reaches the plug test takes [`AIIonCannonPlugValue`](/keys/aiioncannonplugvalue/) in place of the rating an unremarkable structure gets.

:::caution[The flag does not make a structure an upgrade plug]
[`PowersUpBuilding=`](/keys/powersupbuilding/) is what names the host a plug slots into, and everything a fitted plug brings with it follows from occupying that slot rather than from this setting — [a turret for a host that has none](/keys/turret/), [a superweapon granted without the `AuxBuilding=` test](/systems/superweapons/#from-a-structure-or-a-plug). A plug that omits `IsPlug=` is fitted and behaves identically. A structure that names a host in `PowersUpBuilding=` is absorbed into that host and deleted as it is placed, so it never stands on the map and the computer never rates it at all — which is why the shipped rules put this flag on the GDI Upgrade Center, the host that accepts plugs, rather than on the plugs themselves.
:::

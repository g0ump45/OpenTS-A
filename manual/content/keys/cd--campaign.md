---
key: CD
scope: campaign
label: Campaign disc
see_also: ["Scenario", "FinalMovie", "RequiredAddon"]
when_omitted:
  kind: value
  value: "-1"
---

`0` names the GDI disc, `1` the Nod disc and `2` the Firestorm disc, while `-1` names no disc in particular. No disc is ever asked for, so the number survives only as the side the campaign is treated as belonging to.

Two decisions read it. The opening cinematic plays ahead of the first mission's briefing only while the value is below `2`. The loading screen picks its backdrop from a pair of GDI pictures for `0` and a pair of Nod pictures for `1`; anything above `1` falls back to searching the campaign's opening scenario file name for `GDI`, taking the GDI pair when it is found and the Nod pair when it is not.

:::caution[A campaign that names no disc reads its backdrop name from outside the table]
The backdrop table is indexed straight from the disc number, so `-1` lands two places in front of it. The offsets used at 640 by 480, and at 800 by 600 or larger, carry the index back inside the table, but at every other screen size the file name is taken from the bytes in front of it.
:::

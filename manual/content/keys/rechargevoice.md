---
key: RechargeVoice
summary: The EVA line spoken as the superweapon finishes charging.
see_also: ["system:superweapons"]
when_omitted:
  kind: value
  value: none
---

The line is spoken on the frame an ordinary weapon's timer reaches zero, and only for the local player's own weapon. A [`UseChargeDrain=yes`](/keys/usechargedrain/) weapon becomes ready on a separate branch that announces nothing. An unrecognized speech name is not rejected; it leaves the weapon with no line.

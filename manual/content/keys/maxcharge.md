---
key: MaxCharge
summary: The charge a mobile EMP vehicle must reach before it may discharge.
see_also: ["system:emp-pulse"]
when_omitted:
  kind: value
  value: "0"
---

Charge rises by one each frame the vehicle is not immobilized and stops at this figure, so the value is also the number of frames a discharged vehicle needs before its next pulse. With [`PipScale=Charge`](/keys/pipscale/) the pip bar shows the fraction reached.

:::caution[Zero leaves the vehicle permanently ready]
The discharge test passes as soon as the charge is not below `MaxCharge`. At `0` that is true from the moment the vehicle appears, and it stays true after every pulse.
:::

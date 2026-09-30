---
key: StartCharge
summary: The charge a vehicle is created with, which only a mobile EMP vehicle spends.
see_also: ["system:emp-pulse"]
when_omitted:
  kind: value
  value: "0"
---

The value is applied once, as the vehicle is created, and never again: a pulse resets an [`IsMobileEMP=yes`](/keys/ismobileemp/) vehicle's charge to zero and it rebuilds from there. Setting it to [`MaxCharge`](/keys/maxcharge/) or above lets such a vehicle discharge on the frame it arrives.

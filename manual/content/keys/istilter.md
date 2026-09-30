---
key: IsTilter
summary: Parsed flag that no gameplay path reads.
no_effect: true
when_omitted:
  kind: value
  value: "yes"
---

No gameplay path reads the stored flag, so a vehicle's leaning is unaffected by it in either direction. What a vehicle does on sloped ground follows from its [`Locomotor`](/keys/locomotor/) instead.

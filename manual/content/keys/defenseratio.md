---
key: DefenseRatio
summary: Parsed defensive share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", DefenseLimit, GDIBaseDefenseCoefficient, NodBaseDefenseCoefficient]
when_omitted:
  kind: value
  value: ".5"
---

How much of a computer base is given over to defense is decided by [the accumulating build cost of the plan](/systems/ai-base-building/#building-the-plan), scaled by [`GDIBaseDefenseCoefficient`](/keys/gdibasedefensecoefficient/) or [`NodBaseDefenseCoefficient`](/keys/nodbasedefensecoefficient/) according to the house's country name. Those coefficients are the setting that moves the proportion.

---
key: AirstripRatio
summary: Parsed airstrip share of a computer base that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", AirstripLimit, Helipad]
when_omitted:
  kind: value
  value: ".12"
---

No code identifies an airstrip, so there is no group of them for a share to size, and no count for [`AirstripLimit`](/keys/airstriplimit/) to bound either. Aircraft are housed by [`Helipad=yes`](/keys/helipad/) buildings, whose place in a computer plan is settled while [the plan is assembled](/systems/ai-base-building/#building-the-plan).

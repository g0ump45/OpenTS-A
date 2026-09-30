---
key: AirstripLimit
summary: Parsed ceiling on airstrips that the engine never uses.
no_effect: true
see_also: ["system:ai-base-building", AirstripRatio, Helipad]
when_omitted:
  kind: value
  value: "5"
---

No code identifies an airstrip, so there is no count for a ceiling to bound, and none for [`AirstripRatio`](/keys/airstripratio/) to size a share of either.

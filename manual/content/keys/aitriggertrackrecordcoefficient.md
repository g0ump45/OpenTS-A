---
key: AITriggerTrackRecordCoefficient
summary: The multiplier applied to an AI trigger's history term when one of its teams fails.
see_also: ["system:ai-team-production", AITriggerFailureWeightDelta, AITriggerSuccessWeightDelta]
when_omitted:
  kind: value
  value: "1"
---

The history term is the trigger's successes so far minus half its runs so far, and it is scaled by this value on the [failure path only](/systems/ai-team-production/#the-track-record) — the success path uses the same term unscaled. Since the scaled term is then clamped to at most zero, raising the value deepens the penalty a trigger with a poor record takes and changes nothing for a trigger whose record is at or above one success in two. At `0` a failure moves the weight by [`AITriggerFailureWeightDelta`](/keys/aitriggerfailureweightdelta/) alone, regardless of history.

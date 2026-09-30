---
key: HalfDamageSmokeLocation2
summary: Parsed offset that nothing in the engine reads.
no_effect: true
see_also: [HalfDamageSmokeLocation1, DamageSmokeOffset]
when_omitted:
  kind: value
  value: 0,0,0
---

The three components are parsed and stored, and no path reads them back. Where a damaged structure's smoke and sparks actually sit is set by [`DamageSmokeOffset`](/keys/damagesmokeoffset/).

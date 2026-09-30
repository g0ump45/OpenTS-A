---
key: AnimAux2
summary: The first frame, frame count and step delay of a structure's second auxiliary animation.
see_also: ["AnimIdle", "AnimActive", "AnimAux1"]
when_omitted:
  kind: value
  value: "0,1,0"
---

The value has the form [`AnimIdle`](/keys/animidle/) describes, and the same damaged-frame arithmetic applies to it.

One path reaches the sequence. A [`NukeSilo=yes`](/keys/nukesilo/) structure closes its door on it once the missile is away, and drops back to [`AnimIdle`](/keys/animidle/) six game frames later.

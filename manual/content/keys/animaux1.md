---
key: AnimAux1
summary: The first frame, frame count and step delay of a structure's first auxiliary animation.
see_also: ["AnimIdle", "AnimActive", "AnimAux2"]
when_omitted:
  kind: value
  value: "0,1,0"
---

The value has the form [`AnimIdle`](/keys/animidle/) describes, and the same damaged-frame arithmetic applies to it.

One path reaches the sequence. A [`NukeSilo=yes`](/keys/nukesilo/) structure holds its door open on it, between the [`AnimActive`](/keys/animactive/) sequence that opened the door and the [`AnimAux2`](/keys/animaux2/) sequence that closes it, and stays on it for 14 game frames before the missile leaves.

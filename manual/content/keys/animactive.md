---
key: AnimActive
summary: The first frame, frame count and step delay of a structure's working animation.
see_also: ["AnimIdle", "AnimAux1", "AnimAux2"]
when_omitted:
  kind: value
  value: "0,1,0"
---

The value has the form [`AnimIdle`](/keys/animidle/) describes, and the same damaged-frame arithmetic applies to it.

Three structures switch to this sequence: a [`ConstructionYard=yes`](/keys/constructionyard/) structure while something it placed is building, a [`UnitReload=yes`](/keys/unitreload/) structure while it reloads whatever it is in radio contact with, and a [`NukeSilo=yes`](/keys/nukesilo/) structure opening its door for a launch. The silo holds the sequence until it reaches its last frame and then moves to [`AnimAux1`](/keys/animaux1/).

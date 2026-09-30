---
key: Craters
summary: Parsed smudge list that the engine never uses.
no_effect: true
see_also: ["Crater", "Scorches"]
when_omitted:
  kind: value
  value: ""
---

Craters are not chosen from this list. When an animation that forms craters settles on the ground, the engine gathers every registered smudge type carrying [`Crater=yes`](/keys/crater/#scope-smudgetype) that will fit the cell, weighs the size of the marks against the size of the blast, and picks one of the survivors at random. A smudge type reaches that pool through its own setting alone, whether or not it is named here.

Naming a smudge the game does not already know still registers one of that name, so an entry here can add an artless smudge type to the game without the list ever placing it.

---
key: ProductionAnimDamaged
summary: The animation the production slot runs while the structure is damaged.
see_also: ["ProductionAnim", "ConditionYellow"]
when_omitted:
  kind: inherited
  note: The animation ProductionAnim names.
---

Only a [`ConstructionYard=yes`](/keys/constructionyard/) structure ever asks for this name, and only when its health has fallen to [`ConditionYellow`](/keys/conditionyellow/) or below as the animation is created. [ProductionAnim](/keys/productionanim/) covers the three other structures that run the slot and ask for the healthy name instead.

A slot that names only this one and no healthy animation therefore runs nothing on those three, and nothing on a healthy construction yard.

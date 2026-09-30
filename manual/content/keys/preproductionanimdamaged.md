---
key: PreProductionAnimDamaged
summary: The animation the pre-production slot runs while the structure is damaged.
see_also: ["PreProductionAnim", "ConditionYellow"]
when_omitted:
  kind: inherited
  note: The animation PreProductionAnim names.
---

Only a [`ConstructionYard=yes`](/keys/constructionyard/) structure ever asks for this name, and only when its health has fallen to [`ConditionYellow`](/keys/conditionyellow/) or below as the animation is created. An unloading harvester asks for the healthy name however damaged the structure it is docked with, so this one is never reached at a dock.

A slot that names only this one and no healthy animation therefore runs nothing at a dock, and nothing on a healthy construction yard.

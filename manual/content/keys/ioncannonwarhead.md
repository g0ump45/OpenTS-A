---
key: IonCannonWarhead
summary: The WarheadType an ion cannon blast applies its damage through.
see_also: [IonCannonDamage, "system:superweapons"]
when_omitted:
  kind: value
  value: none
---

The blast passes [`IonCannonDamage`](/keys/ioncannondamage/) through this warhead with no source, so nothing is credited with the kills, but the damage is otherwise ordinary: the warhead's [`Verses`](/keys/verses/) table and [`Immune=yes`](/keys/immune/) both apply. The warhead also controls the radius the damage falls off over, the impact animations it selects, its terrain and bridge effects, and whether the strike lights the scene.

The same warhead is used by the [Ion-cannon strike](/mapping/actions/taction-ion-cannon/) trigger action, which creates a blast directly without any superweapon involved.

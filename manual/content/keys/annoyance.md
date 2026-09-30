---
key: Annoyance
summary: Makes a team that is already under way regroup when one of its members is fired on.
see_also: [Suicide, Stray, "system:base-attacked"]
when_omitted:
  kind: value
  value: "no"
---

Damage to a member is handed to its team, and what the team does with it depends on whether it has begun to move. A team that has not begun to move always drops its center point and goes back to regrouping and reforming, wherever the damage came from. A team that is under way normally answers by turning on the attacker instead, and this setting adds the regroup to that case: the center point is dropped and the team reforms before it presses on with its script.

Four conditions gate the moving case, and all four are already required before this setting is consulted: the damage must have a source, that source must not itself be a member of the team, it must not already be the team's target, and one member of the team — the one that most recently joined, not the one that was hit — must be a non-aircraft carrying a primary weapon.

:::caution[The regroup happens even when the target does not change]
The regroup is set before the two tests that call the retarget off, and it clears the team's center point — which is the first thing the range test accepts. A team of this type that is already shooting at something armed therefore always stops to reform and never turns on its attacker; only a team with no armed current target reaches the second test, which calls the retarget off for an aircraft attacker.
:::

[`Suicide=yes`](/keys/suicide/) switches the whole damage response off, this setting included.

---
key: RetargetAccuracy
summary: The chance that a bomblet from a splitting projectile keeps the carrier's own target.
see_also: [Splits, AirburstWeapon, Cluster]
when_omitted:
  kind: value
  value: "0"
---

Only a [`Splits=yes`](/keys/splits/) projectile reads the figure. It is a fraction from `0` to `1`, and a percentage is accepted and divided by a hundred, so `75%` and `0.75` are the same assignment.

Every bomblet is decided separately. At this chance it inherits the carrier's target; otherwise it takes one at random from a list of candidates, and that pick is struck off the list so the next bomblet draws a different one. `0` sends every bomblet to the random draw and `1` sends every one at the carrier's target. A carrier whose target was destroyed before the burst always draws at random whatever the figure says.

The candidate list holds every object standing within five cells of the carrier's target, or of the carrier itself when it was aimed at a cell. When fewer than [`Cluster`](/keys/cluster/) objects are standing there, the list is padded with bare cells drawn up to three cells away in each direction from the same point, so a burst always has somewhere to aim.

:::caution[The candidate list ignores ownership]
Nothing filters the list by house, so the firer's own units, its allies and the firer itself are all candidates. A bomblet that draws the firer is redrawn on an even chance, and the second draw can land on the firer again. A low figure on a weapon fired from within a group of friendly units therefore scatters bomblets across that group.
:::

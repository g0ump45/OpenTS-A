---
key: Strength
scope: overlaytype
label: Wall damage threshold
see_also: ["system:walls-and-gates", "DamageLevels"]
when_omitted:
  kind: value
  value: "1"
  note: At that figure almost every hit clears the threshold outright, so a segment advances a stage on nearly anything that reaches it.
---

```ini title="rules.ini"
[GAWALL]
Strength=100
```

For a wall overlay, `Strength` is not a health pool. Each hit is evaluated independently:

- Damage greater than or equal to `Strength` advances the wall by one damage stage.
- Positive damage below `Strength` succeeds when a random integer from `0` through `Strength` is less than the damage.
- A failed hit leaves no damage to accumulate for the next hit.

With `Strength=100`, a hit for `20` therefore has a `20 / 101` chance, about 19.8%, to advance the wall by one stage.

A stage that lands is a stage regardless of how much damage carried it, so a wall's durability is the number of stages [`DamageLevels`](/keys/damagelevels/) grants multiplied by how often a hit clears this threshold — never the sum of the damage taken. Raising `Strength` past the largest damage figure that will ever reach the wall does not make it invulnerable; it only reduces every hit to the chance above.

Two fixed damage figures ignore the threshold in practice. The [cascade into neighboring segments](/systems/walls-and-gates/#stepping-through-the-stages) and the hit dealt to a wall run when a wall tower is removed both carry 200 damage, which clears any threshold of 200 or below outright.

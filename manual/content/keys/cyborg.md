---
key: Cyborg
summary: Lets the soldier survive a killing hit on its stumps, and exposes it to EM pulses.
see_also: [Strength, BerzerkAllowed, ConditionRedSparkingProbability, CollateralDamageCoefficient, "system:emp-pulse"]
when_omitted:
  kind: value
  value: "no"
---

Damage that would take a standing cyborg to zero strength does not kill it. Its strength is set to a quarter of its [`Strength`](/keys/strength/#scope-aircrafttype) instead, never below `1`, it is forced prone and put into the crawl animation, `[AudioVisual] InfantryExplode` plays at its position, and the hit is reported as the transition into condition red rather than as a destruction — so nothing that watches for a kill sees one. Damage delivered as unavoidable, such as the impact that kills anything dropped from a height, skips all of that and kills outright.

Once it is prone the reprieve is spent: the next killing hit plays [`InfantryExplode`](/keys/infantryexplode/) again and removes the soldier immediately, with no death animation and no corpse.

Two more behaviors attach to the flag. With [`BerzerkAllowed=yes`](/keys/berzerkallowed/) in `[CombatDamage]`, the hit that first takes a cyborg below half strength turns it berzerk once and puts it on Area Guard; a berzerk soldier [ignores allegiance](/systems/target-selection/#why-a-candidate-is-rejected) when it picks targets. And a cyborg is the only infantry an [EM pulse](/systems/emp-pulse/#what-a-pulse-reaches) stuns — ordinary soldiers walk through one untouched.

The flag also settles two type-level figures as the section is read. It is what makes an InfantryType eligible for [damage sparks](/keys/conditionredsparkingprobability/) at all, and it selects the starting [`CollateralDamageCoefficient`](/keys/collateraldamagecoefficient/).

:::caution[A prone cyborg does not get up when re-ordered]
Ordering a prone soldier of a player-controlled house to the same destination twice normally makes it stand and run. A cyborg is excluded from that, as a [`Fraidycat=yes`](/keys/fraidycat/) soldier is, so it crawls the whole way.
:::

:::caution[The collateral figure is chosen before the flag is read]
The shared object-type block runs before an InfantryType reads its own flags, so the coefficient is picked from the value the flag held on the *previous* rules layer. A section that first declares `Cyborg=yes` is given the non-cyborg figure of `0.66` on that pass and only takes `0.33` on a later layer that carries the section again. Writing [`CollateralDamageCoefficient`](/keys/collateraldamagecoefficient/) in the same section settles it either way, because that key is read immediately afterward.
:::

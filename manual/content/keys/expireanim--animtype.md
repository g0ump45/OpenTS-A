---
key: ExpireAnim
scope: animtype
label: Animation impact effect
see_also: ["Damage", "Warhead", "ExpireSound", "Bouncer"]
when_omitted:
  kind: value
  value: none
---

An animation of the named type is created where a thrown animation ends its life, provided that end does not come low over water: solid ground, a bridge deck, and anything more than about a cell and a half above the ground all take this path. An animation that ends low over water makes a wake and a small splash instead — a meteor plays the last animation of the rules' [`SplashList`](/keys/splashlist/) — and this setting is not consulted there.

The end comes on the first contact of the flight, so the impact effects and the [`BounceAnim`](/keys/bounceanim/#scope-animtype) effects can both appear on the same frame at the same place.

:::caution[The impact blast sits inside the same branch]
[`Damage`](/keys/damage/#scope-animtype) and the flash of light that goes with a bright warhead are applied in the same block as the animation. An animation with nothing named here therefore deals no blast damage whatever its damage figure and [`Warhead`](/keys/warhead/#scope-animtype) say. The damage dealt on a strike is a separate path and still applies.
:::

A value naming no registered animation is not refused: a type of that name is created on the spot, holding no artwork and every setting at its built-in value.

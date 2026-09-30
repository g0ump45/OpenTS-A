---
key: CloakingSpeed
summary: The number of game frames an object spends on each stage of its cloaking fade.
see_also: [CloakingStages, "system:cloaking"]
when_omitted:
  kind: value
  value: "7"
---

Both fades step through the stages counted by [`CloakingStages`](/keys/cloakingstages/) at this rate, so the value sets how long the object spends part way visible in each direction. A lower figure makes it disappear and reappear faster. [Hiding an object](/systems/cloaking/#the-four-states) covers what each stage looks like.

A structure fades on its own fixed schedule of fifteen translucency steps, one per frame, and never reads this value.

:::danger[A rate of zero strands an object part way back]
A fade that starts at zero frames per stage never advances. The disappearing fade repairs that for itself by falling back to one frame per stage, but the reappearing fade does not: a `CloakingSpeed=0` vehicle, infantryman or aircraft that is forced out of a cloak sticks at the stage the fade began on — drawn as a ripple to other players and shadowy to its owner — and from there it can neither finish returning nor hide again. Because standing part way through a fade counts as cloaked, a vehicle or infantryman stuck this way can never fire again either; an aircraft still fires, since only a fully hidden aircraft is refused a shot.
:::

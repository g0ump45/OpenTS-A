---
key: Weight
summary: How strongly an object resists being rocked, and how heavily it presses on ice.
when_omitted:
  kind: value
  value: "1"
---

A blast near a voxel object tips it, and this figure divides the force: the tilt is scaled by `(0.04 - distance × 0.000025) × force ÷ Weight`, ignored below `0.01` and capped at `0.05`, with the forward component taking half of that scale and the sideways component all of it. A heavier object therefore shrugs off a jolt that would rock a lighter one, and past the cap a lighter figure buys no more tilt. Only an object drawn from a voxel model is rocked at all, so the figure does nothing on a type drawn from shapes.

In the snow theater the figure is also weighed against two rules-wide thresholds each time a vehicle finishes entering a cell. A vehicle reaching [`IceBreakingWeight`](/keys/icebreakingweight/) breaks the ice under it and one that only reaches [`IceCrackingWeight`](/keys/icecrackingweight/) cracks it; the sinking and the stun follow either outcome. Both tests run on vehicles alone.

Both thresholds are met on equality. The stock figures put the harvester at `1` and most tanks at `3.5`, against a cracking threshold of `2` and a breaking threshold of `4`, so a harvester crosses stock ice untouched, a tank cracks it, and the civilian recreational vehicle at `4` is the only stock type heavy enough to go through.

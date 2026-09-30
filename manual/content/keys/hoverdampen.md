---
key: HoverDampen
summary: Fraction of its vertical motion a hovering unit keeps from one frame to the next.
see_also: [HoverHeight, HoverBob, Gravity]
when_omitted:
  kind: value
  value: ".8"
---

Every frame the cushion adds its lift, subtracts [`Gravity`](/keys/gravity/), and then multiplies what is left over by this fraction. Subtracting `Gravity` is a constant pull rather than a decay, so this fraction is the only thing that bleeds a bounce away: below `1` a hover unit that has been shoved down or has crossed a rise settles back to [its rest height](/keys/hoverheight/) instead of oscillating about it. The stock rules write it as `40%`, which the engine reads as `0.4`. The levitation locomotor damps on the same fraction.

:::caution[At 1 and above the bounce never settles]
A fraction of `1` keeps the whole of the accumulated vertical motion and leaves a hover unit swinging about its rest height for as long as it exists; above `1` the swing grows every frame, though touching the ground clears the accumulated motion and starts it over.
:::

---
key: VeteranRatio
summary: The multiple of its own cost an object must destroy to earn one point of experience.
see_also: ["system:veterancy"]
when_omitted:
  kind: value
  value: "10"
---

Each credited kill adds the destroyed type's cost divided by the product of the killer's own cost and this value, so an expensive killer needs proportionally more wreckage than a cheap one for the same promotion. At the default, an object must destroy ten times its own cost to reach veteran and twenty times to reach elite. [Earning experience](/systems/veterancy/#earning-experience) covers what counts as a credited kill.

Lowering the value speeds every promotion by the same factor; raising it slows them. It has no bearing on the ranks handed out by crates, armories, reinforcements, or drop pods.

:::caution[Zero divides]
The kill formula divides by this value multiplied by the killer's own cost, and neither figure is guarded. A `VeteranRatio` of `0`, or a killer type whose [`Cost`](/keys/cost/) is `0`, divides by zero.
:::

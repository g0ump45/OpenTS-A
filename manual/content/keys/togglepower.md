---
key: TogglePower
summary: Whether the player may switch this structure on and off.
see_also: ["system:power"]
when_omitted:
  kind: value
  value: "yes"
---

The power cursor offers the toggle only on a selectable, player-controlled structure of a type that is `TogglePower=yes` and either drains power or is [`Powered=yes`](/keys/powered/). `TogglePower=no` therefore takes the structure out of the player's reach, but it does not keep the structure switched on: the [Turn off building](/mapping/actions/taction-turn-off-attached/) trigger action and a scenario's own structure record reach the same switch and require only drain or `Powered=yes`.

:::caution[A TogglePower=no defense is silenced but stays lit]
The shutdown test that takes a structure out of service, and the branch that darkens its powered animations and lights, both spare a `TogglePower=no` structure; the weapon lockout and the SAM tracking stall do not, so such a defense holds fire through a shortfall while still running its idle animations. [Defenses](/systems/power/#defenses) sets the tests side by side.
:::

---
key: Difficulty
summary: The campaign difficulty as a slider position, 0 for Easy, 1 for Normal and 2 for Hard.
see_also: ["system:difficulty"]
when_omitted:
  kind: value
  value: "1"
---

Both the difficulty slider on the campaign selection screen and the one in the game options — the latter only while no game is running — write this position, and both offer the three settings only. The value is used at the start of each campaign mission: it becomes the [difficulty slot](/systems/difficulty/#from-the-setting-to-a-slot) of every house under the player's control, and `2` minus it becomes the slot of every other house. A scenario outside a campaign ignores it and takes its difficulty from the session instead.

:::danger[A value above 2 is used as an index anyway]
The read accepts anything from 0 to 4 and clamps only to that range. Starting a campaign mission does map those five positions onto the three slots, but reading the scenario then overwrites both slots with the raw value again, so that narrowing never survives. A value of `3` or `4` becomes a slot of 3 or 4, and the computer's slot becomes `-1` or `-2`; both are then used directly to index the three difficulty sections and every per-difficulty list in `[General]`.
:::

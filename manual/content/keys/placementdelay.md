---
key: PlacementDelay
summary: Minutes a factory waits before trying again when the object it finished cannot leave yet.
see_also: ["system:ai-base-building"]
when_omitted:
  kind: value
  value: ".05"
---

The value is converted to whole game frames when the delay is set, and it is set only on the temporary-blockage outcome: an object whose exit is permanently obstructed is abandoned immediately, and one that leaves cleanly is handed to the house at once. Only production attached to a building runs through this timer, which is how a computer house builds; a player's production is placed from the sidebar instead. For a structure, the blockage that starts the wait is [an allied ground object standing in the placement zone](/systems/ai-base-building/#choosing-a-spot).

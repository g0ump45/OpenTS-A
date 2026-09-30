---
key: TeamDelays
summary: The frames a house waits between team creation passes, one entry per difficulty.
see_also: ["system:ai-team-production"]
when_omitted:
  kind: value
  value: ""
  note: The list stays empty and the difficulty slot is used to index it anyway, reading storage that was never allocated.
---

Entries run hardest game setting first, and a computer house indexes them with its own difficulty slot, which is the inverse of the setting the player chose. The value is reloaded after every [team creation pass](/systems/ai-team-production/#when-the-pass-runs); the very first countdown of a house also carries `175` frames for each place it holds in the house list, so houses stagger their passes rather than running them together.

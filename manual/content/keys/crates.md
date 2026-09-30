---
key: Crates
summary: Starting state of the crates option for a multiplayer or skirmish match.
see_also: ["system:crates"]
when_omitted:
  kind: value
  value: "yes"
---

The value seeds the match's crate option when a session begins, and the game setup screen then writes over it. The starting placement pass and the expiry sweep both read the resulting match option, not this setting.

:::caution[Pickup replacement also checks this setting]
A collected crate is replaced only when both this key and the match option are enabled. `Crates=no` in the rules with crates switched on for the match therefore suppresses pickup replacement while the expiry sweep keeps running; switching crates off for the match suppresses both paths whatever this key contains.
:::

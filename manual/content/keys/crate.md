---
key: Crate
summary: Whether the overlay is a crate, which infantry and vehicles collect by entering its cell.
see_also: ["system:crates"]
when_omitted:
  kind: value
  value: "no"
---

The flag alone decides what counts as a crate. Infantry, walkers, hovercraft and driven vehicles all collect the overlay by entering its cell, and the one that entered receives a result; a computer-controlled house's infantry refuse to enter such a cell at all, and its vehicles refuse in a campaign. Outside a campaign, an overlay carrying this flag is stripped out of a map's overlay layer as the map is read.

Being a crate does not by itself make an overlay one of the two the engine places or recognizes in a campaign result lookup. [`WoodCrateImg`](/keys/woodcrateimg/) and [`CrateImg`](/keys/crateimg/) name those separately, and [Choosing the result](/systems/crates/#choosing-the-result) covers what each of them delivers.

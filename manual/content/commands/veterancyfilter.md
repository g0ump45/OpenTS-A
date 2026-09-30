---
command_id: VeterancyFilter
---

Sorts the selected objects the player controls into three ranks, elite, veteran and rookie, as [veterancy](/systems/veterancy/) defines them. On a mixed selection the first press keeps only the highest rank present and remembers the whole selection. While the selection is still that remembered group, one of its ranks, or two of them together, each further press moves to the next rank of the group, wrapping from rookie back to elite. A selection that matches none of those starts over, and a selection of one rank alone does nothing. [`VeterancyFilterAddLower`](/commands/veterancyfilteraddlower/) grows the selection back instead of replacing it. The remembered group is forgotten when the scenario ends, and neither command acts while a structure is being placed.

---
key: RevealByHeight
summary: Whether high ground between a looker and a cell blocks that cell from being revealed.
see_also: ["system:map-visibility", Sight]
when_omitted:
  kind: value
  value: "yes"
---

At `yes` each candidate cell is checked against a single probed cell — the candidate's ground cell, displaced two cells on both axes and then stepped once toward the looker — and the reveal is refused while that probed ground stands more than three height levels above the looker. At `no` the check is skipped and every cell inside the sight radius is revealed regardless of the terrain between.

Switching it off also turns on a second behavior. The shortcut that lets an object which moved one cell rescan only the outer rings is guarded on this flag being `no`, so at the default every look scans its full disc and only `RevealByHeight=no` makes the cheaper scan reachable.

[The scan](/systems/map-visibility/#the-scan) covers both, including which cell is probed.

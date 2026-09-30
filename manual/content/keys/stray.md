---
key: Stray
summary: Distance in cells a team member may drift from the team before it is ordered back.
see_also: [CloseEnough, GuardSlower, "system:ai-team-execution"]
when_omitted:
  kind: value
  value: "2"
  note: "512 leptons."
---

The figure is written in cells, with fractions accepted, and multiplied by 256 as it is read. It is the tolerance every test that holds a team's formation together applies: a member that has drifted farther than this from the team's center, or from the destination the team is moving to, is ordered back rather than left where it is, and until it is back the team does not count as gathered or as having arrived. An aircraft is allowed three times the distance, and one team mission measures twice it. [Team execution](/systems/ai-team-execution/#keeping-the-members-together) sets out the individual tests and which of the two distances each one measures.

One test outside teams reads it: a ground object beginning a path search toward a temporarily blocked cell redirects itself to a passable cell nearby only while it is farther away than its check distance, and a member of a team measures that against this figure where every other object measures it against [`CloseEnough`](/keys/closeenough/).

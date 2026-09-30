---
key: Aggressive
summary: Lets a member that holds a target stay and fight instead of closing on the team's destination.
see_also: [Stray, Suicide, "system:ai-team-execution"]
when_omitted:
  kind: value
  value: "no"
---

While a team is [coordinating a move](/systems/ai-team-execution/#moving), each member is measured against the destination. A member is put on the Move mission and sent there under **Any of:**

- it is farther from the destination than [`Stray`](/keys/stray/), which is tripled for an aircraft;
- **All of:** it is below ground level, and the team's next script line is not itself a move;
- **All of:** it is an aircraft, it is still in the air, it is not already over the destination, and the team's next script line is not itself a move.

The team does not count as having arrived until none are left outstanding.

On an aggressive team a member that holds a target is passed over at that point. It is neither given the move order nor counted as outstanding, so the rest of the team can finish the move and start the next script mission while it stays where it is and keeps shooting. A member with no target is treated exactly as it would be on any other team.

The exemption belongs to the move step alone. Nothing about it changes recruitment, or the regroup that follows damage, or the gathering a stopped team does.

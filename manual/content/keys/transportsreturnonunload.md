---
key: TransportsReturnOnUnload
summary: Sends each transport back to where it set out from once the team's unload finishes.
see_also: [Passengers, "system:ai-team-execution"]
when_omitted:
  kind: value
  value: "no"
---

Two steps make up the behavior, and both belong to the team rather than to the transport type.

Every time the team coordinates a move toward a target, each member whose type sets [`Passengers`](/keys/passengers/) above zero and has not already recorded a return point stamps the cell it is standing in as one. The stamp survives repeated passes within one script mission, because a member that already carries a return point is passed over. It does not survive the mission itself: the team clears every member's record as it advances to the next line of its script, including the advance into the Unload mission, so the cell handed back at release is whatever the record holds at that moment rather than the cell taken during the preceding move. The record is a shared field that other missions also write.

Then, once an [Unload](/mapping/missions/tmission-unload/) mission has emptied every transport, each transport is dropped from the team, given that recorded cell as its destination and put on the Move mission, and its record is cleared so a later trip can take a fresh one. The unload mission's own group parameter still decides what becomes of the members that carry no passengers, but it no longer has any say over the transports — they are released whichever setting it names.

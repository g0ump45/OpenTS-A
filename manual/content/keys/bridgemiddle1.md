---
key: BridgeMiddle1
summary: Position within a bridge tile set of the first of the five middle pieces of an east-west span.
see_also: [BridgeSet, TrainBridgeSet, BridgeMiddle2, BridgeStrength]
when_omitted:
  kind: value
  value: "-1"
  note: The position lands two tiles before the set's first piece rather than on a piece of it.
---

A position is counted from one, so the piece at position `p` is the tile `p - 1` past the set's first, and every test reverses that arithmetic: a cell's position is its tile index minus the set's first tile plus one. The ten `Bridge` position keys serve both bridge tile sets — a road span is measured from [`BridgeSet`](/keys/bridgeset/) and a railway span from [`TrainBridgeSet`](/keys/trainbridgeset/), and the same ten positions describe the pieces of either.

This position and the four that follow it are the condition ladder for the middle sections of an east-west span: whole, connected one way, connected the other, connected both ways, then destroyed. A hit sets the struck section to the third position outright, whatever it showed before, and ages the sections either side of it: the one toward the top-left or top-right end moves a place along the ladder, while the one toward the opposite end keeps the piece it had. An engineer's [repair](/systems/capture/#repairing-a-bridge) puts the whole run back at the first position. A middle section spans several cells drawn from one piece, and changing the piece carries the change to every neighboring cell that still shows the old one.

The first four positions of the five also decide whether a struck cell is treated as a high bridge at all. A cell at one of them, or at one of the first four of [`BridgeMiddle2`](/keys/bridgemiddle2/), or one whose bridge deck carries a high bridge overlay, goes to the high bridge handler; the destroyed position is not among them. Bridge destruction must be switched on for the scenario and the warhead must be a [wall destroyer](/keys/wall/#scope-warheadtype), after which [`BridgeStrength`](/keys/bridgestrength/) is what the damage is weighed against.

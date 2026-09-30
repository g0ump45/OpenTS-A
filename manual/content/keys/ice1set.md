---
key: Ice1Set
summary: First of the three sixty-four-tile ice sets a snow theater provides.
see_also: [Ice2Set, Ice3Set, IceShoreSet]
when_omitted:
  kind: value
  value: "-1"
  note: No tile set is selected, so the role stays unresolved.
---

Ice comes in three sets of the same shape, and every sixty-four-tile set is laid out identically: offsets 0 through 15 are full ice, offset 16 is the cracked tile, and offsets 17 through 63 are the edge pieces that run ice up against everything else. The three exist only so that a frozen stretch does not repeat one pattern — whenever the engine lays ice it picks one of the three at random, so a theater that resolves some but not all of them will place unresolved ice a third or two thirds of the time.

Which variant a full-ice cell takes is decided from its four orthogonal neighbors much as blending works elsewhere, except that the neighbors being tested for are full ice rather than a ground type. The write is shifted: the pass lays offset 0 when all four neighbors are ice and the pattern plus one otherwise, so offset 1 is never written and a cell with no ice around it lands on offset 16, the cracked tile. Edge pieces are chosen from the pattern of ice across all eight neighbors instead, sharing their lookup with [`IceShoreSet`](/keys/iceshoreset/) on the land side of the same boundary.

All of this is gated on the snow theater, and none of it is gated on the role resolving.

Ice thickens and refreezes only while the scenario has ice growth turned on, but cracking does not: a vehicle crossing ice or an explosion over it can crack and break a sheet in any snow scenario.

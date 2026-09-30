---
key: ShroudGrow
summary: Whether the shroud creeps back over terrain that nothing is watching.
see_also: ["system:map-visibility", ShroudRate]
when_omitted:
  kind: value
  value: "no"
---

At `no` revealed terrain stays revealed for the rest of the match unless a scenario re-shrouds it. At `yes` the [regrowth pass](/systems/map-visibility/#shroud-regrowth) runs on the interval [`ShroudRate`](/keys/shroudrate/) sets, taking one cell off the edge of the revealed area each time.

The flag gates only that timer. The [Creep shadow back in](/mapping/actions/taction-creep-shadow/) trigger action performs the same pass whatever this value is.

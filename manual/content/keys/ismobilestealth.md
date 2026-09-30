---
key: IsMobileStealth
summary: Marks a deployed structure as a mobile stealth generator, one of the kinds treated as a deployed vehicle.
see_also: [DeploysInto, UndeploysInto, CloakGenerator]
when_omitted:
  kind: value
  value: "no"
---

The flag is one of the eight that make a structure [one of the deployed-vehicle kinds](/keys/deploysinto/), and membership in that set is its whole effect. Such a structure is put down on the deploying vehicle's own cell rather than one cell away and returns to that cell when it undeploys, may be taken back down whether or not the session allows redeploying, and has sparks attached by [an EM pulse](/systems/emp-pulse/#what-a-pulse-reaches) as it is stunned.

Unlike the other kinds in that set, this one carries nothing of its own — no facing, no gun handling, no cloaking. The field a mobile stealth generator projects comes from [`CloakGenerator=yes`](/keys/cloakgenerator/), which any structure may carry, and the type it packs back into from [`UndeploysInto`](/keys/undeploysinto/).

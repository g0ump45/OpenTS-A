---
key: IsCoreDefender
scope: buildingtype
label: Core defender structure
see_also: [DeploysInto, UndeploysInto, "system:emp-pulse"]
when_omitted:
  kind: value
  value: "no"
---

The flag is one of the eight that make a structure [one of the deployed-vehicle kinds](/keys/deploysinto/): put down on the deploying vehicle's own cell rather than one cell away, returned to that cell when it undeploys, and taken back down whether or not the session allows redeploying.

[An EM pulse](/systems/emp-pulse/#what-a-pulse-reaches) then passes over it. Every other structure the blast catches is powered off and stunned for the pulse's duration; a core defender takes neither, and the sparks that would mark a deployed vehicle are part of the same branch it skips. Its paralyzed trigger event springs regardless.

---
key: HarvesterDumpRate
summary: Minutes a docked harvester spends handing over each stored unit.
see_also: ["system:tiberium", "HarvesterLoadRate", "Storage"]
when_omitted:
  kind: value
  value: ".016"
---

The dumping counter advances one step per frame and releases one unit each time it reaches this many minutes' worth of steps, at 900 frames to the minute. The default therefore moves one unit roughly every 15 frames, and a full harvester takes that long for every unit it carries.

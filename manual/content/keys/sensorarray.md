---
key: SensorArray
summary: Whether the structure marks the cells around it as sensed, revealing cloaked objects standing there.
see_also: ["system:power", "system:cloaking"]
when_omitted:
  kind: value
  value: "no"
---

Coverage is stamped in one pass over every cell within [`CloakRadiusInCells`](/keys/cloakradiusincells/) the first time the structure comes online, and only while it is operational — an array that opens while the shutdown test holds it out of service marks nothing. It is lifted when the structure is taken off the map, and lifting it makes every other operational array re-mark its own cells so that overlapping coverage is not lost with it.

Marking a cell reveals a cloaked object standing on it to the array's house, and a fully faded enemy structure on a marked cell is made visible again as a shadowy outline.

:::caution[A shortfall does not lift sensor coverage]
Unlike a [cloak generator](/keys/cloakgenerator/), which collapses its field the moment the base runs short of power, an array keeps every cell it has already marked; coverage is given up only when the structure is taken off the map. What low power costs it is the refresh — the re-marking that runs when a cloak field finishes growing, or when another array gives up its cells, skips an array that is switched off, stunned or short of power.
:::

---
key: ProductionAnim
summary: The animation a structure runs while its work is in progress.
see_also: ["ProductionAnimDamaged", "ProductionAnimX", "ProductionAnimY", "ProductionAnimYSort", "ProductionAnimZAdjust", "PreProductionAnim", "ActiveAnim", "system:production"]
when_omitted:
  kind: value
  value: ""
---

The value names an animation registered in `[Animations]`, which the structure runs as an attached animation on the terms [Building animations](/systems/building-animations/) covers: a separate object pinned to a point on the structure's artwork, cycling on its own timing, and created and destroyed as the structure changes state. Only the first 15 characters of the name are kept, and a name no `[Animations]` entry registers creates nothing.

Four kinds of structure use the slot, each at its own moment.

| Structure | The slot starts | The slot ends |
| --- | --- | --- |
| [`ConstructionYard=yes`](/keys/constructionyard/) | The structure it built reports that its buildup has finished | Nothing stops it |
| [`Refinery=yes`](/keys/refinery/) | The docked harvester has emptied the last of its load, or the docked harvester is given a destination and a queued mission other than harvest | Nothing stops it |
| [`UnitRepair=yes`](/keys/unitrepair/) | The bay begins repairing the vehicle standing over it | The repair finishes, the house cannot pay for the next step, contact with the vehicle drops, or the bay leaves the repair mission |
| [`WeaponsFactory=yes`](/keys/weaponsfactory/) | The door begins opening for a finished vehicle | Nothing stops it |

Where nothing stops the slot, an animation that plays to its end empties it and a looping one holds it.

:::caution[A refinery's looping animation holds the harvester at the dock]
The harvester waits while the refinery's slot is running and leaves on the first pass that finds it empty. An animation that loops never empties it, so the harvester stays docked and its house stops collecting.
:::

:::caution[Only a construction yard reaches the damaged form]
The construction yard picks between the two names from its own health. The refinery, repair bay and weapons factory each ask for the healthy one however damaged they are, so [`ProductionAnimDamaged=`](/keys/productionanimdamaged/) on those three is never used. Because creating an animation in the healthy form restarts every animation the structure is running in that form, each of those three moments also drops a damaged structure's other animations back to their healthy versions until its health next crosses [`ConditionYellow`](/keys/conditionyellow/).
:::

## Where the settings are read

The two animation names are read from the structure's `[<Image ID>]` art entry, while the offset and the two draw-order biases are read from the entry named after the BuildingType itself; [where each setting is read from](/systems/building-animations/#where-each-setting-is-read-from) sets that split out for every slot. On the ordinary structure, which sets no [`Image=`](/keys/image/), those are the same entry and the split is invisible. A type that borrows another structure's artwork has to write the two halves in two places.

```ini title="rules.ini"
[MYPROC] ; example refinery BuildingType
Image=NAREFN ; its art entries are read from [NAREFN]
```

```ini title="art.ini"
[NAREFN] ; the Image ID entry supplies the two names
ProductionAnim=NAREFN_AR
PreProductionAnim=NAREFN_A

[MYPROC] ; the type's own entry supplies the offsets and biases
ProductionAnimX=-2
ProductionAnimY=2
ProductionAnimZAdjust=-100
```

The four are read only once the slot holds a name — either the healthy one or the damaged one is enough. Unlike an active slot, this one has no power flags: a production animation is never frozen or dropped by a power shortfall.

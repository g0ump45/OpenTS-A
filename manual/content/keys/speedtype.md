---
key: SpeedType
summary: The terrain table column a vehicle's per-cell throttle and passability are read from.
see_also: ["Crusher", "MovementZone", "TrackedUphill", "WheeledUphill", "Speed"]
when_omitted:
  kind: context-dependent
  note: "`Track` in a `Crusher=yes` section and `Wheel` in every other."
---

One `rules.ini` section per [land type](/reference/enums/land-type/) — `[Clear]`, `[Road]`, `[Water]` and the rest — carries one figure per [speed type](/reference/enums/speed-type/) token, and this key picks which of those figures the vehicle reads out of every one of those sections.

```ini title="rules.ini"
[Water]
Track=0
Wheel=0
Hover=1

[MYSKIMMER] ; a UnitType registered in [VehicleTypes]
SpeedType=Hover
MovementZone=AmphibiousDestroyer
```

Two decisions read the chosen column. A cell whose figure is `0` is refused when the vehicle asks whether it may step into it, unless the question is asked at the height of a bridge deck over that cell, or with no height at all — a vehicle standing at ground level under a bridge is refused exactly as it would be in the open. The second decision belongs to the drive locomotor alone: a driven vehicle crosses every other cell at the fraction of full speed the figure gives, after the slope multiplier that the same value selects — `Track` takes [`TrackedUphill`](/keys/trackeduphill/) and [`TrackedDownhill`](/keys/trackeddownhill/), while every other speed type — `Foot`, `Hover`, `Amphibious` and the rest alike — takes [`WheeledUphill`](/keys/wheeleduphill/) and [`WheeledDownhill`](/keys/wheeleddownhill/). A vehicle moved by any other locomotor reads its column for the per-step test and nothing else, so a hovercraft or a tunneler crosses ground priced at a tenth of full speed at the same speed it crosses ground priced at full. [Movement and terrain](/systems/movement-and-terrain/#what-each-locomotor-drives-its-speed-from) sets out where each of the ten takes its speed from.

## SpeedType and MovementZone

[`MovementZone`](/keys/movementzone/) answers a different question. Every cell is sorted once into one of a handful of terrain classes, and connected runs of cells sharing a class become the zones that reachability is judged against; a type's movement zone says which of those classes count as connected for it. That sorting reads the `Wheel` entry of a land type and no other, after `Water` and `Beach` cells have already been set aside as water — so a vehicle's own `SpeedType` never changes which cells the game treats as connected.

The two settings therefore have to agree. A hovercraft whose `[Water] Hover=` is above zero still gets no route across a lake unless its movement zone accepts water, because the zone map never consulted the `Hover` column; and a movement zone that accepts water still strands it if its own column reads `0` for `Water`, because the per-step check refuses each cell as it is reached.

:::danger[An unrecognized value leaves the type with no speed type at all]
The value is matched against the token list and nothing else, and a spelling that misses resolves to no speed type rather than to a fallback. The repair that gives an unset speed type its `Track` or `Wheel` starting value runs before this key is read, so it cannot undo the bad value; only a later rules layer that names the same section again gets another chance at it. Until then every throttle and passability question about the vehicle is answered from one slot short of the terrain table's first column — the four bytes before the table's first entry, which for every land type but `Clear` belong to the entry before it.
:::

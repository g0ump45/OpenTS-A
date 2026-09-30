---
key: WheeledDownhill
summary: Speed multiplier for a vehicle that is not tracked stepping to a lower cell.
see_also: [WheeledUphill, TrackedUphill, TrackedDownhill, SpeedType]
when_omitted:
  kind: value
  value: "1"
---

Each cell of a vehicle's journey is costed as a fraction of full speed, drawn from the movement table its [`SpeedType`](/keys/speedtype/) selects, and that fraction is multiplied by this value when the ground under the destination cell stands lower than the ground under the vehicle. A step of two or more terrain levels is costed from the Road row of that table rather than from the destination's own land type. Ground heights are what is compared, so a ramp counts as a descent exactly as a cliff edge does, and a step between cells of equal height takes neither this multiplier nor [`WheeledUphill`](/keys/wheeleduphill/).

The name is narrower than the rule. Only `SpeedType=Track` is sorted off to [`TrackedDownhill`](/keys/trackeddownhill/); every other SpeedType a vehicle can carry — `Wheel`, `Hover`, `Float`, `Amphibious`, `Foot`, `Creep`, `Winged` — descends on this value. Infantry and aircraft take neither pair, and neither does a vehicle whose [`Locomotor`](/keys/locomotor/) hovers or tunnels rather than driving.

:::caution[The multiplier is applied after the terrain cost is capped]
The terrain cost is clamped to full speed first and this value is applied afterwards, so a figure above `1` — as the stock `1.2` is — carries a vehicle downhill faster than it moves on the flat. A product of exactly zero is then replaced with half speed, so `WheeledDownhill=0` halves a descent rather than forbidding one.
:::

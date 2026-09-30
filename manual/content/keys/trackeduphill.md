---
key: TrackedUphill
summary: Speed multiplier for a tracked vehicle stepping to a higher cell.
see_also: [TrackedDownhill, WheeledUphill, WheeledDownhill, SpeedType]
when_omitted:
  kind: value
  value: "1"
---

Each cell of a vehicle's journey is costed as a fraction of full speed, drawn from the movement table its [`SpeedType`](/keys/speedtype/) selects, and that fraction is multiplied by this value when the ground under the destination cell stands higher than the ground under the vehicle. A step of two or more terrain levels is costed from the Road row of that table rather than from the destination's own land type. Ground heights are what is compared, so a ramp counts as a climb exactly as a cliff edge does, and a step between cells of equal height takes neither this multiplier nor [`TrackedDownhill`](/keys/trackeddownhill/).

The multiplier reaches vehicles only, and among them only those carrying `SpeedType=Track`; every other SpeedType on a vehicle takes [`WheeledUphill`](/keys/wheeleduphill/) instead, whatever its name suggests. It is also the ground drive's rule alone, so a vehicle whose [`Locomotor`](/keys/locomotor/) hovers or tunnels climbs at an unmodified speed.

:::caution[The multiplier is applied after the terrain cost is capped]
The terrain cost is clamped to full speed first and this value is applied afterwards, so a figure above `1` carries a tracked vehicle uphill faster than it moves on the flat. A product of exactly zero is then replaced with half speed, so `TrackedUphill=0` halves a climb rather than forbidding one.
:::

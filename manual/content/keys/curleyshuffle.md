---
key: CurleyShuffle
summary: Whether an attacking aircraft picks a fresh firing position between shots.
when_omitted:
  kind: value
  value: "no"
---

With the flag off, an aircraft that has reached a firing position and has its target in range stays there and fires again for as long as it holds ammunition and a target. With it on, the aircraft fires twice from each position and then goes back to choosing a new one, flies there, and starts again.

The flag is read only inside the attack mission, and only on the branches where the aircraft is already in range: an aircraft that is out of range chooses a fresh position either way. A strafing run is exempt on both counts — its five shots are spaced by the weapon's rate of fire and never consult the flag.

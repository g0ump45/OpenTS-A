---
key: TargetLaserTime
summary: Frames the sighting laser stays drawn after a vehicle fires.
see_also: ["system:action-lines", TargetLaser, TargetLaserColor]
when_omitted:
  kind: value
  value: "15"
---

Each shot a vehicle with [`TargetLaser=yes`](/keys/targetlaser/) fires restarts its laser's timer at this many frames, and the line is drawn while the timer runs. The default is one second at the game's frame rate. `0` starts no timer, so the laser is never drawn.

```ini title="UI.INI"
[Ingame]
TargetLaserTime=30
```

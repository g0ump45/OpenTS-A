---
key: StandingFrames
summary: The number of frames in one facing's standing artwork of a shape-drawn vehicle.
see_also: ["StartStandFrame", "WalkFrames", "FiringFrames", "Facings"]
when_omitted:
  kind: computed
  note: 1 for a vehicle whose FiringFrames is above 0, and 0 otherwise.
---
At `0` the vehicle has no standing artwork of its own and is drawn from the first frame of its facing's walk run instead. Above `0` a vehicle at rest in a cell it occupies is drawn at [`StartStandFrame`](/keys/startstandframe/) plus its facing block times this count, and the count is also the stride the engine assumes between one facing's standing run and the next. The count is kept in a single signed byte, so `256` stores as zero and any figure above `127` stores as a negative number.

```ini title="art.ini"
[REAPER] ; the Image ID of the stock Cyborg Reaper
Facings=8
StandingFrames=1
StartStandFrame=0
```

:::caution[The standing artwork never animates]
Only the first frame of a facing's standing run is ever drawn. Nothing advances a resting vehicle through the run, so a count above `1` reserves frames that the vehicle never shows and pushes the derived [`StartFiringFrame`](/keys/startfiringframe/) further up the file for nothing.
:::

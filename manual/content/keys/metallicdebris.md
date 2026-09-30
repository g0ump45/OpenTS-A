---
key: MetallicDebris
summary: The animations three different paths throw up as wreckage — an ion storm strike, a collapsing bridge, and an object destroyed with no debris types of its own.
see_also: [IonStormWarhead, "system:ion-storms"]
when_omitted:
  kind: value
  value: ""
---

```ini title="rules.ini"
[AudioVisual]
MetallicDebris=MYDEBRIS1,MYDEBRIS2 ; AnimTypes registered in [Animations]
```

Between two and six animations are drawn from the list, each picked independently, and all of them are created at the strike point. That path uses the list only when the bolt [changed the cell](/systems/ion-storms/#what-a-strike-does): a building or object in it is gone, the terrain height moved, or the cell was empty road, rock, wall, or weeds before the bolt landed.

Two other paths draw from the same list. A [bridge](/systems/walls-and-gates/) cell being destroyed throws one on an even chance, alongside the bridge explosion itself. And an object destroyed with a [`MaxDebris`](/keys/maxdebris/) above zero but no [`DebrisTypes`](/keys/debristypes/) of its own falls back to this list, taking a random count up to `MaxDebris` and creating them all just above its center. That fallback indexes the list without checking it holds anything, so a type reaching it while this list is empty reads through a null pointer and crashes as soon as the random count comes out above zero. The bridge path indexes it the same way and the ion storm path picks from it the same way, so an empty list is a crash on all three.

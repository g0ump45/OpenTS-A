---
key: FireUp
summary: The stage of the upright firing animation at which an infantry type releases its round.
see_also: ["FireProne", "Sequence", "JumpJet"]
when_omitted:
  kind: value
  value: "0"
---

A soldier that opens fire starts its firing animation, and the round is released on the update where the animation stage matches this figure. The figure counts stages of the run named `FireUp` in the type's [`Sequence`](/keys/sequence/) section, from `0`, so the default releases the round on the same update the animation starts. [`FireProne`](/keys/fireprone/) covers the same stage for a soldier lying down, and a [`JumpJet=yes`](/keys/jumpjet/) soldier plays its `FireFly` run instead but still releases on this stage.

```ini title="art.ini"
[E1] ; the Image ID of the stock Light Infantry
Sequence=E1Sequence
FireUp=2 ; the third stage of E1Sequence's six-frame FireUp run
```

If the shot cannot be taken when the stage arrives, the soldier abandons the firing animation and returns to standing, or to prone if it was lying down.

:::caution[A stage past the end of the run is never reached]
The stage is matched for exact equality. A figure above the frame count of the run therefore never comes up, and the soldier never releases its round.
:::

---
key: DropPod
summary: The marks a drop pod leaves on the ground where it touches down.
see_also: [Droppod, AtmosphereEntry, DropPodPuff, "system:drop-pods"]
when_omitted:
  kind: value
  value: ""
---

```ini title="rules.ini"
[AudioVisual]
DropPod=MYPOD_NE,MYPOD_NW,MYPOD_SE,MYPOD_SW ; AnimTypes registered in [Animations]
```

One entry is created at the landing cell on the frame the passenger is successfully placed there. [Touchdown](/systems/drop-pods/#touchdown) covers the slot each of the four approach directions selects and what happens when the list is empty; a blocked touchdown destroys the passenger and creates nothing from this list at all.

A name that the [`[Animations]` list](/formats/rules-registries/) does not register is created here instead of being rejected. The stock list ends with two such names, `DROPPODY` and `DROPPODY2`, so the marks the south-east and south-west approaches select come into being from this assignment alone.

This is not the TeamType flag. [`Droppod`](/keys/droppod-teamtype/) with a lowercase second `p` is a separate key.

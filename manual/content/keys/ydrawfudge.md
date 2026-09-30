---
key: YDrawFudge
summary: Pixels a terrain object's artwork is shifted down the screen by.
when_omitted:
  kind: value
  value: "0"
---

The figure is added to the vertical screen position the object draws at, so a positive figure moves the artwork down the screen and a negative one lifts it. It is applied to three things: the position of the ordinary draw, the position of the depth-free draw used for an object held on the cursor before it is placed, and the render rectangle worked out once when the object is placed, which is what the tactical map dirties when the object needs refreshing.

```ini title="rules.ini"
[MYROCK]         ; example boulder whose artwork sits high in its frame
YDrawFudge=-6    ; lift it six pixels so it meets the ground
```

Both draws also bias the object's depth by the figure, and they do not do it the same way. The ordinary draw divides the figure by three and discards the remainder, so any figure from `-2` to `2` biases the depth by nothing at all; the cursor draw applies the whole figure. Only the ordinary draw governs how a placed object sorts against its neighbors.

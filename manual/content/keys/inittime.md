---
key: InitTime
summary: Parsed number that the engine never uses.
no_effect: true
when_omitted:
  kind: value
  value: "10000"
---

The value is stored on the scenario as the map is opened and written back out by the map editor, which is why nearly every shipped mission carries `InitTime=10000`. Nothing between those two points reads it: no timer starts from it, no countdown is seeded with it, and no gameplay path reads it at all.

---
key: CloakRadiusInCells
summary: The radius in cells of a cloak generator's field or a sensor array's coverage.
when_omitted:
  kind: value
  value: "20"
---

A [`CloakGenerator=yes`](/keys/cloakgenerator/) structure grows its field out to this radius one cell per game frame, and a [`SensorArray=yes`](/keys/sensorarray/) structure marks every cell within it as sensed in a single pass. A type that is neither reads the value and never spends it. The value is stored in a single byte, so figures above `127` wrap negative.

The same radius sizes the ellipse drawn on the tactical map for a selected cloak generator or sensor array whose type also sets [`HasRadialIndicator=yes`](/keys/hasradialindicator/), which appears only while that structure is switched on and its house is player-controlled.

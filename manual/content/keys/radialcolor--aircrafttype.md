---
key: RadialColor
scope: aircrafttype
label: Ring color
when_omitted:
  kind: value
  value: 0,0,0
---

```ini title="rules.ini"
[MYCLOAK] ; example BuildingType
CloakGenerator=yes
CloakRadiusInCells=12
HasRadialIndicator=yes
RadialColor=0,168,240
```

The ellipse and the four spokes sweeping round it are drawn in this color. Only a structure that draws a [radius ring](/keys/hasradialindicator/) reads it; every other type in this scope stores the value and never uses it.

The engine default is black, and black is drawn rather than skipped, so a type that asks for a ring without naming a color gets a black one.

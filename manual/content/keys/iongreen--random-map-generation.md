---
key: IonGreen
scope: random-map-generation
label: Random map generation
see_also: [UseIonStorms, "system:ion-storms"]
when_omitted:
  kind: context-dependent
  note: The green tint the scenario is holding when generation reads this file.
---

Random map generation reads this entry from the hard-coded file `ION.INI`, and only when the seed carries [`UseIonStorms=yes`](/keys/useionstorms/). It replaces the value the generated map was built with, so that file is where a mod sets the storm lighting every generated map will use.

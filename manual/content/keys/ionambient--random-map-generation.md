---
key: IonAmbient
scope: random-map-generation
label: Random map generation
see_also: [UseIonStorms, "system:ion-storms"]
when_omitted:
  kind: context-dependent
  note: The ambient level generation has just set from the seed's time of day.
---

Random map generation reads this entry from the hard-coded file `ION.INI`, and only when the seed carries [`UseIonStorms=yes`](/keys/useionstorms/). It replaces the value the generated map was built with, so that file is where a mod sets the storm lighting every generated map will use.

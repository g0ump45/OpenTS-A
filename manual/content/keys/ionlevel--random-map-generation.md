---
key: IonLevel
scope: random-map-generation
label: Random map generation
see_also: [UseIonStorms, "system:ion-storms"]
when_omitted:
  kind: context-dependent
  note: The scenario's current height brightness truncated to a whole number, because the fallback divides two whole numbers. Generation sets that value to a thousandth of full light just beforehand, so the fallback yields 0.
---

Random map generation reads this entry from the hard-coded file `ION.INI`, and only when the seed carries [`UseIonStorms=yes`](/keys/useionstorms/). It replaces the value the generated map was built with, so that file is where a mod sets the storm lighting every generated map will use.

The fallback cannot carry an ordinary height brightness across, so a generated map is shaded flat through every storm unless `ION.INI` states this value outright.

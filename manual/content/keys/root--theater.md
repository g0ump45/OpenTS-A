---
key: Root
scope: theater
label: Theater archive root
see_also: [IsoRoot, Suffix]
when_omitted:
  kind: context-dependent
  note: "`TEMPERAT` for TEMPERATE and `SNOW` for SNOW, which keep their original settings; for any other theater, the theater's own name."
---

The root names three files: `<Root>.MIX`, the archive the theater's artwork is read from; `<Root>.PAL`, the palette everything on the map is drawn through; and `<Root>.INI`, the [theater control file](/formats/theater-control/) listing its tile sets.

```ini title="rules.ini"
[DESERT]
Root=DESERT     ; DESERT.MIX, DESERT.PAL and DESERT.INI
```

A missing palette is survivable and a missing control file is not: where no `<Root>.PAL` is found the game builds a placeholder gradient and carries on, but a theater whose control file is absent declares no tile sets and every cell of a map drawn in it is empty.

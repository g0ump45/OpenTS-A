---
key: IsoRoot
scope: theater
label: Theater tile archive root
see_also: [Root, Suffix]
when_omitted:
  kind: context-dependent
  note: "`ISOTEMP` for TEMPERATE and `ISOSNOW` for SNOW, which keep their original settings; for any other theater, the theater's own name."
---

`<IsoRoot>.MIX` is the archive the isometric tile artwork is read from. It is separate from [`Root`](/keys/root/) because the tile artwork of a theater is far larger than the rest of it and ships in an archive of its own.

```ini title="rules.ini"
[DESERT]
IsoRoot=ISODES  ; ISODES.MIX
```

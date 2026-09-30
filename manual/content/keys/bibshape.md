---
key: BibShape
summary: The apron shape drawn on the ground under a structure.
see_also: ["Bib", "ExtraLight", "Foundation"]
when_omitted:
  kind: value
  value: ""
  note: No apron shape is loaded and none is drawn.
---

The value is a filename without its extension, and only a non-empty value is taken. The named `<value>.SHP` is loaded with the rules, and refetched on the same occasions and with the same theater rewrite [`DoorAnim`](/keys/dooranim/) describes.

The shape is drawn under every structure of the type that is not still building, after the structure’s own shape and one pixel nearer the viewer, with the structure's [`ExtraLight`](/keys/extralight/) folded into its brightness. The frame drawn is the structure's own current frame number, so an apron that is to change with the structure's condition needs the same frame layout the main artwork has.

```ini title="art.ini"
[MYWEAP] ; example war factory, drawn from its own Image ID
BibShape=GAWEAPBB ; loaded as GTWEAPBB.SHP in temperate
```

The apron is folded into the rectangle a structure of the type is redrawn within, and it is drawn on the fogged copy as well. What it does not do is enlarge the footprint or open it to traffic — that is [`Bib=yes`](/keys/bib/), which is read on the rules side and never looks at this artwork.

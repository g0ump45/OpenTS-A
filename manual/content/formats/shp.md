---
format_id: shp
title: SHP images
summary: Stores indexed two-dimensional image frames used by sprites and interface graphics.
kind: binary
extensions:
  - .SHP
role: image
source_files:
  - code/shapeset.h
  - code/objtype.cpp
  - code/builtype.cpp
---

An SHP file opens with a short header carrying the frame count and the logical width and height every frame is placed within, followed by one record per frame and then the frame data itself. Each record holds that frame's offset inside the logical box, its own width and height, the position of its pixels in the file, one color standing in for the whole frame so the radar can draw a cell without examining it, and two flags marking whether the frame carries transparent pixels and whether its pixels are run length encoded.

Non-voxel object art, animations, cursors and interface graphics all use SHP data. Cursors and interface graphics are asked for by fixed names written into the engine. Object art is named from the type's [Image ID](/keys/image/) plus `.SHP`, and two art settings change that name before the file is looked up. [`Theater=yes`](/keys/theater/) replaces the extension with the theater's own — `.TEM` in temperate and `.SNO` in snow — and leaves the rest of the name alone. Failing that, [`NewTheater=yes`](/keys/newtheater/) keeps the `.SHP` extension and rewrites the second letter of the name instead, to `T` in temperate and `A` in snow, but only where the first two letters are `GA`, `NA`, `GT`, `NT`, `CA` or `CT`. A name that starts with anything else is left as written even with the setting on, and a type carrying both settings takes the first.

Whichever name is arrived at is fetched from a cached archive rather than opened as a file, so object art has to be a member of an archive that startup cached; [MIX archives](/formats/mix/) covers which those are. A type whose artwork is not found is left with no image rather than with a placeholder.

For a BuildingType, `Image=` in `art.ini [<Image ID>]` selects the basename of the main SHP. It does not change the building's Image ID or the section used by other building art keys.

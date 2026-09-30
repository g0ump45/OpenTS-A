---
key: Name
scope: multiplayer-maps
label: Multiplayer map title
see_also: ["Official"]
when_omitted:
  kind: value
  value: "No Name"
---

Loose `.mpr` files sitting in the game directory are scanned whenever the multiplayer map list is rebuilt, and each file's title becomes the row it occupies in that list, unless the same file also carries a `[Multiplay] Description`, which replaces it. The title travels with the map: the host sends it to the guests with the rest of the game options, so every player sees the same text beside the map preview.

At most 43 characters survive into the list, whatever the file holds.

Maps packaged inside a `.pkt` list are titled from the packet entry instead and never consult this setting.

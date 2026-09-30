---
key: Description
scope: map-packets
label: Packet list entry
see_also: [CD, MinPlayers]
when_omitted:
  kind: computed
  note: An empty entry. The read writes its own empty default into the description and nothing supplies a substitute, so the map is listed under a blank line.
---

A scenario packet lists its maps in `[MultiMaps]`, and each entry names the section the map describes itself in. The text read from that section is the row the map occupies in the multiplayer scenario list, and it is what the host sends to the other machines as the scenario name.

```ini title="MyMaps.PKT"
[MultiMaps]
1=MYMAP

[MYMAP] ; the section the entry above named
Description=Four player canyon
```

At most 43 characters are kept; a longer line is cut. The map file the entry stands for is the section name with `.MAP` appended, and it is consulted only for the digest the other players' copies are checked against — never for a better description, unlike a loose map file.

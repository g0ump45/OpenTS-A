---
key: Description
scope: multiplayer-maps
label: Loose map list entry
see_also: [CD, MinPlayers, Name, Official]
when_omitted:
  kind: computed
  note: The map's own [Basic] Name, which the listing is built with before this section is read, or "No Name" when that is absent as well.
---

A loose `.MPR` in the game directory is listed under the text in its own `[Multiplay]` section. That row is what the multiplayer scenario list shows and what the host sends to the other machines as the scenario name.

```ini title="MyMap.MPR"
[Multiplay]
Description=Four player canyon
```

An empty value is treated the same as a missing one, so blanking the assignment falls back to [`Name`](/keys/name/) rather than producing an empty row. At most 43 characters are kept; a longer line is cut.

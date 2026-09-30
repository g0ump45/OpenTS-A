---
key: MinPlayers
scope: map-packets
label: Packet-listed player limits
see_also: [MaxPlayers, Description]
no_effect: true
when_omitted:
  kind: value
  value: "2"
---

```ini title="MyMaps.PKT"
[MYMAP] ; a section named by the packet's [MultiMaps] list
MinPlayers=2
```

The value is read into the entry's minimum player count. That count is private to the listing and nothing reads it afterwards, so neither the lobby, the starting-position pass nor the house assignment consults it: a map declaring `MinPlayers=2` can still be started with eight players.

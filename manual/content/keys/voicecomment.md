---
key: VoiceComment
summary: The idle remark and the disembarking remark a soldier speaks, in that order.
see_also: [Passengers]
when_omitted:
  kind: value
  value: ""
---

Exactly two entries are read, and each has its own trigger.

| Entry | Played when |
| --- | --- |
| First | The soldier runs its second idle animation while unselected and owned by the local player, on a one-in-three roll |
| Second | The soldier first reaches the center of a cell after a transport has set it down and the tether is cut |

```ini title="rules.ini"
[MYCIVILIAN] ; example InfantryType
VoiceComment=21-I000,21-I002 ; entries registered in the sound list
```

The idle animation itself is one of eleven outcomes drawn each time the soldier's idle timer expires, and three of those eleven run the second animation, so the first entry is heard on roughly one idle in eleven. Both sounds play at the soldier's own position rather than through the speech channel, and an entry naming a sound the game does not register is dropped as the list is read — which shifts every later entry down one place. Entries past the second are never read at all.

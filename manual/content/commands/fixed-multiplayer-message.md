---
command_id: fixed:multiplayer-message
---

A function key opens a message editor only while all of these hold:

- the session is neither a campaign nor a skirmish game;
- the key falls in the session player range, which runs from `F1` to `F1` plus the session's player limit less one;
- no message is already being edited.

Past that gate only a network or Internet session opens anything. The last key in the range starts a message to everyone, and an earlier key starts a private message to one connection, the one at the position the key names, which requires a connection at that position and that the player may still send a private message. [In-game chat](/systems/chat/) states who may. A message to the team, and a second key for everyone, are commands of their own: [`ChatToAllies`](/commands/chattoallies/) and [`ChatToAll`](/commands/chattoall/).

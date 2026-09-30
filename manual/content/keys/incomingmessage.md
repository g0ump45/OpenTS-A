---
key: IncomingMessage
summary: Sound played whenever a line is added to the on-screen message list.
see_also: [MessageDelay]
when_omitted:
  kind: value
  value: none
---

```ini title="rules.ini"
[AudioVisual]
IncomingMessage=CHAT1 ; a sound ID registered in SOUND.INI
```

The name suggests chat, but the sound sits inside the routine that adds any line to the message list drawn over the tactical view, so it plays at full volume for every one of them. That includes lines a single-player game raises on its own: the low power warning, the ion storm notices, text from a trigger action, the message a house gets when it is defeated, and the warning that another player changed the game options. A line that finds no free message buffer is dropped without the sound.

Chat from another player is added the same way, and so is your own line as it is sent, so each is heard once. A line too long for the message area is split, playing the sound once per piece.

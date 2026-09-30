---
key: AIDetectDisguise
summary: Lets every computer house see a disguised soldier for what it is when it scans for a target.
see_also: [DetectDisguise, Disguised, "system:target-selection"]
when_omitted:
  kind: value
  value: "no"
---

```ini title="rules.ini"
[AI]
AIDetectDisguise=yes
```

With `AIDetectDisguise=yes` a [`Disguised=yes`](/keys/disguised/) soldier no longer escapes the scan a computer-controlled house makes, so a computer opponent will acquire and fire on a spy walking into its base. A house a player controls is unaffected and still passes the disguised soldier over, which leaves the disguise working against the player exactly as before.

The distinction is drawn on who controls the house rather than on which house is local, so every machine in a networked game reaches the same answer. In a campaign a house the mission has handed to the player counts as player-controlled for this purpose.

Where the ability belongs to particular units rather than to a whole side, give those types [`DetectDisguise=yes`](/keys/detectdisguise/) instead; the two work independently and either one is enough.

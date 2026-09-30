---
key: TimerInherit
summary: Whether this mission resumes the countdown timer the previous one finished with.
see_also: [CarryOverMoney]
when_omitted:
  kind: value
  value: "no"
---

```ini title="map file"
[Basic]
TimerInherit=yes
```

The mission countdown is captured when a campaign mission is won and handed to the next one along with the carried-over money. With the switch set, and only if the captured timer had time left on it, the new mission starts that timer running from where the last one stopped. With the switch clear, or with a captured timer of zero, the new mission starts with its countdown stopped and a trigger action has to start one.

Nothing is inherited across a loss and replay: the same captured timer is applied again each time the mission is restarted.

---
key: Recruitable
summary: Whether an object in this mission may be taken onto a team.
see_also: ["system:ai-team-production", "system:base-attacked"]
when_omitted:
  kind: value
  value: "yes"
---

The setting lives in a mission's own section and is read from the mission the candidate is currently in, not from the mission of anything doing the recruiting. At `no` a team passes the object over, and so does the tally that decides what a computer house builds to fill its teams.

```ini title="rules.ini"
[Sleep]
Recruitable=no
```

The [base defense call-up](/systems/base-attacked/#which-objects-qualify) reads it as well, but only in a campaign game. Outside a campaign that one test is skipped, so an object parked in a mission marked this way is still pulled back to fight an attacker even though no team may recruit it.

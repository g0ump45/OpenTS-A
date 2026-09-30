---
key: LooseRecruit
summary: Parsed TeamType flag that the engine never uses.
see_also: ["system:ai-team-production", Recruiter, Group]
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

[Recruitment](/systems/ai-team-production/#recruitment) is widened by [`Recruiter=yes`](/keys/recruiter/) and by a [`Group`](/keys/group/#scope-teamtype) of `-2`, neither of which reads this flag. Every team in the shipped `ai.ini` and `aifs.ini` spells the key out along with the rest of its settings, all 420 of them as `LooseRecruit=no`.

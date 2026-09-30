---
key: Autocreate
summary: Which of an object's two recruitable states a team of this type reads when it recruits.
see_also: ["system:ai-team-production", AreTeamMembersRecruitable, Recruiter]
when_omitted:
  kind: value
  value: "no"
---

A team of an unmarked TeamType accepts only an object whose ordinary team-recruitable state is set and pays no attention to its autocreate-recruitable state; a marked one does exactly the reverse. Both states start set on every object, so the choice matters only once a scenario or an earlier team has cleared one of them.

:::caution[Being suggested sets the mark for the rest of the session]
The mark is not only an input. Every TeamType an AI trigger suggests is marked as autocreated at the moment of suggestion and stays marked, so `Autocreate=no` survives only until the first pass that names the type. Nothing in [trigger selection](/systems/ai-team-production/#which-triggers-are-eligible) reads the value.
:::

---
key: Whiner
summary: Parsed flag that the engine never reaches.
see_also: ["system:base-attacked"]
no_effect: true
when_omitted:
  kind: value
  value: "no"
---

Damage to an infantry or a vehicle takes one of two branches: a member of a team hands the damage to its team, and everything else goes down the second branch. The flag is tested on that second branch, behind a condition that only an object with no team can satisfy, so a team member never reaches it and an object that could reach it has no team to read the flag from. Every team in the shipped `ai.ini` and `aifs.ini` spells the key out along with the rest of its settings, and 58 of the 420 carry `Whiner=yes`, which changes nothing. [Settings and state without effect](/systems/base-attacked/#settings-and-state-without-effect) covers what a damaged team does instead.

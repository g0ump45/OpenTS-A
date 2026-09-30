---
key: CompEasyBonus
summary: Whether a computer house drops one difficulty slot when the session holds more than one human player.
see_also: ["system:ai-team-production"]
when_omitted:
  kind: value
  value: "yes"
---

The drop is applied outside a campaign game, as computer players are assigned, and only to a house that is not already in slot 0. Because a computer house sits in the inverse of the chosen setting's slot, dropping a slot moves it toward the harder end: on the Medium setting such a house lands in the slot the Hard setting would have given it.

The shift is not confined to the combat and production biases of the difficulty sections. Every per-difficulty rules list the house reads moves with it, and so does the [difficulty flag its AI triggers are tested against](/systems/ai-team-production/#difficulty).

---
key: MultiplayerAICM
summary: The percentage of its own starting money added to each computer house outside a campaign, one entry per difficulty.
see_also: ["system:difficulty"]
when_omitted:
  kind: value
  value: ""
  note: The list stays empty and the difficulty slot is used to index it anyway, reading storage that was never allocated.
---

The grant is worked out once, as a scenario outside a campaign finishes loading, for every computer house that is not [`MultiplayPassive=yes`](/keys/multiplaypassive/). The house's credits plus the value of the Tiberium it holds are multiplied by the entry as a percentage, and the result is handed to it **on top of** what it already had. An entry of `100` therefore leaves the house with twice its starting money, not the same amount, and an entry of `0` changes nothing.

Entries run hardest game setting first, and each computer house indexes them with its own [difficulty slot](/systems/difficulty/#from-the-setting-to-a-slot), which in a skirmish is the inverse of the setting chosen for the session, and a slot easier again once the session holds more than one person and the [easy-game bonus](/systems/difficulty/) applies. A campaign game never reaches this list.

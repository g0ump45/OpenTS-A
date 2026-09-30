---
key: Tiberium
scope: warheadtype
label: Sets Tiberium off
see_also: ["system:tiberium", "ChainReaction"]
when_omitted:
  kind: value
  value: "no"
---

A [`ChainReaction=yes`](/keys/chainreaction/) Tiberium overlay detonates under a warhead carrying this flag, and a sonic wave sets it off with no warhead check; under every other warhead the overlay is inert. The flag means nothing to overlays that are not Tiberium, whose cells hold no Tiberium to set off.

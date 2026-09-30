---
key: Armor
scope: housetype
label: Armor bias
see_also: ["system:difficulty", Verses]
when_omitted:
  kind: value
  value: "1.0"
---

Each country carries its own divisor, and a house takes the one belonging to the country it was created under — outside a campaign game, the country chosen for it in the session setup. Damage arriving at that house's objects is divided by it, so a figure above 1 in one country's section and not another's makes everything that country fields harder to kill, whatever it is built from.

The divisor is multiplied with [the difficulty section's](/keys/armor/#scope-difficulty-settings) once, when the house is [given its difficulty slot](/systems/difficulty/#how-the-figures-are-combined), and a campaign game drops it: nothing a country section says about armor reaches a campaign mission. Because the two are multiplied before anything divides by the result, a `0` written here does what a `0` in a difficulty section does.

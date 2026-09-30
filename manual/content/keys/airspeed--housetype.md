---
key: Airspeed
scope: housetype
label: Country air-speed multiplier
see_also: ["system:difficulty", Groundspeed]
when_omitted:
  kind: value
  value: "1.0"
---

Each country carries its own multiplier in its own section, and a house of that country combines it with [the difficulty section's](/keys/airspeed/#scope-difficulty-settings) and with [`GameSpeedBias`](/keys/gamespeedbias/) once, at [the moment it is given its difficulty slot](/systems/difficulty/#how-the-figures-are-combined). A campaign game drops the country's contribution and keeps the other two, which is how [`Groundspeed=`](/keys/groundspeed/#scope-housetype) is treated as well.

What does set an aircraft's speed is traced under [the difficulty setting of the same name](/keys/airspeed/#scope-difficulty-settings).

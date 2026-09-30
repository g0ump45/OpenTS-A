---
key: Helipad
summary: Lets a BuildingType accept an aircraft as a docking target and be approached at its docking cell rather than its center.
see_also: ["system:ai-base-building"]
when_omitted:
  kind: value
  value: "no"
---

The building answers a load request from an aircraft and refuses one from anything else, a player may order an aircraft into one that is neither in radio contact nor holding cargo, and an empty carryall ordered into one lands at ground level. While [the base plan is assembled](/systems/ai-base-building/#building-the-plan), a type carrying this flag is appended one to three extra times, so a computer house plans several of them wherever it plans one.

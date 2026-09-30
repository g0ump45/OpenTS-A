---
key: Powered
summary: Whether the structure stops working while its house cannot meet its drain.
see_also: ["system:power"]
when_omitted:
  kind: value
  value: "no"
---

Every low-power shutdown test pairs this with drain: a structure is shut down by low power only when it is `Powered=yes` and its [`Power=`](/keys/power/#scope-buildingtype) is negative. Setting one without the other leaves the structure running through any shortfall. [What low power costs](/systems/power/#what-low-power-costs) traces which of its functions each test stops.

```ini title="rules.ini"
[MYOBEL] ; example laser defense that goes dark at low power
Power=-150
Powered=yes
```

The value has two effects that need no drain. It qualifies the structure to be switched off, since both the power cursor and the [Turn off building](/mapping/actions/taction-turn-off-attached/) trigger action accept a structure that either drains power or is `Powered=yes`. And a [`CloakGenerator=yes`](/keys/cloakgenerator/) structure left at `Powered=no` keeps rebuilding its field during a shortfall instead of waiting for full power.

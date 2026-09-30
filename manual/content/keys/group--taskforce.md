---
key: Group
scope: taskforce
label: TaskForce recruitment group
see_also: ["system:ai-team-production"]
when_omitted:
  kind: value
  value: "-1"
---

The value is read only through the TeamTypes that use the TaskForce, and only by those that leave their own [`Group`](/keys/group/#scope-teamtype) at `-1`. Setting it therefore gives one recruitment group to every TeamType built on this composition at once, and any of those TeamTypes overrides it by naming a group of its own.

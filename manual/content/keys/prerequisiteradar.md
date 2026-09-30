---
key: PrerequisiteRadar
summary: The BuildingTypes that satisfy a RADAR prerequisite.
see_also: ["system:production"]
when_omitted:
  kind: value
  value: ""
---

Owning at least one live structure of any type on this list satisfies a `RADAR` entry in a [`Prerequisite=`](/keys/prerequisite/) list. The entries are alternatives, not requirements: the first one the house owns ends the search, and order carries no other meaning.

The list is read as BuildingType IDs without regard to case, and a name matching none is dropped. An empty list leaves `RADAR` impossible to satisfy, which blocks every type naming it.

---
key: Scenario
scope: campaign
label: Campaign opening mission
see_also: ["CD", "Description", "FinalMovie"]
when_omitted:
  kind: value
  value: ""
  note: An empty name, which starts nothing.
---

The value is the map file the campaign begins with, and it is folded to upper case as it is stored. Choosing the campaign from the mission list starts that file as its first mission; a campaign that names no file fails to start and drops back to the menu.

The same stored name is searched for `GDI` whenever the campaign's disc number is above `1`, which is how a Firestorm campaign's loading screen decides which side's artwork to draw.

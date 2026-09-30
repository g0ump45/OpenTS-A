---
key: Description
scope: campaign
label: Campaign list entry
see_also: ["Scenario", "RequiredAddon", "FinalMovie"]
when_omitted:
  kind: computed
  note: The campaign's own name, as the battle list spells it.
---

The text is the row the campaign occupies in the mission selection list, so it is the only part of a campaign the player ever sees before choosing it. Campaigns the running expansion does not allow are left out of that list, and their text is never displayed.

At most 127 characters are kept; a longer line is cut.

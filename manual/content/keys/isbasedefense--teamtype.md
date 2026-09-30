---
key: IsBaseDefense
scope: teamtype
label: Defensive team
when_omitted:
  kind: value
  value: "no"
---

Every live team built from such a TeamType raises its house's defensive team count, which is weighed against [`MinimumAIDefensiveTeams`](/keys/minimumaidefensiveteams/) while [`UseMinDefenseRule`](/keys/usemindefenserule/) is on before an AI trigger may spring. The team creation pass counts a house's live defensive teams again for itself and caps them against [`MaximumAIDefensiveTeams`](/keys/maximumaidefensiveteams/). An AI trigger whose first TeamType is defensive, and whose second is defensive or absent, is itself handled as a defensive trigger.

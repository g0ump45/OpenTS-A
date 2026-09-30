---
key: Nominal
summary: Shows the type's real name to a player it is not allied with, instead of a generic label.
see_also: [Technician, Crewed, Invisible]
when_omitted:
  kind: value
  value: "no"
---

```ini title="rules.ini"
[MYPRISON] ; a BuildingType registered in [BuildingTypes]
Nominal=yes
```

Holding the cursor over an object names it. An object belonging to a house the player is allied with always gives its own [`Name=`](/keys/name/); one belonging to anybody else is normally reduced to a generic label — "Enemy Soldier" for infantry, "Enemy Vehicle" for a vehicle or an aircraft, "Enemy Structure" for a building. This key is what exempts a type from that reduction, so a civilian or story structure keeps its real name for every player on the map. A structure placed by a map file can carry the same exemption on the individual building, whatever its type says.

The flag has a second, unrelated use on InfantryTypes. A structure's [survivor](/systems/capture/#survivors) of a `Nominal=yes` type is marked a technician, which relabels it, keeps it out of its house's infantry tally and bars it from being lifted out as a civilian evacuee; [`Technician`](/keys/technician/#scope-global-rules) covers which structures mark their survivors that way.

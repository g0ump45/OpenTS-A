---
key: Crushable
scope: animtype
label: Crushable by vehicles
no_effect: true
see_also: [CrushSound, Strength, Crusher]
when_omitted:
  kind: value
  value: "no"
---

An animation is never entered into a cell's occupier list — an AnimType is not a footprint type, so placing one down registers nothing with the cell it sits over. Four of the seven tests that read the flag are fed from that list, and a fifth takes the object under the cursor, which comes from the same list; the remaining two are handed a vehicle's attacker or its target, and an animation can be neither. No gameplay path reads the flag for an animation.

The setting is read out of `art.ini` rather than `rules.ini`, because an AnimType takes all of the settings it shares with other object types from the art database.

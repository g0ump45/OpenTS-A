---
key: LegalTarget
scope: animtype
label: Animation targetability
no_effect: true
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "no"
---

Every path that reads the flag is closed to an animation. The automatic scans weigh only objects a house owns and can be shot at, and the cursor test takes whatever sits nearest the pointer out of a cell's occupier list — a list an animation is never entered into, an AnimType not being a footprint type. An animation attached to a unit or a structure moves and draws with it and still cannot be pointed at; the object underneath answers for both.

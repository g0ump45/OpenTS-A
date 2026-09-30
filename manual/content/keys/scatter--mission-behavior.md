---
key: Scatter
scope: mission-behavior
label: Mission allows scattering
see_also: [Paralyzed, Zombie, PlayerScatter]
when_omitted:
  kind: value
  value: "yes"
---

The setting lives in a mission's own section and is read from the mission the object being asked to move is currently in. At `no` the request is refused at the top of the routine, before anything else about the object or the threat is looked at. [`PlayerScatter`](/keys/playerscatter/) covers the separate decisions that lead to a request being made in the first place.

```ini title="rules.ini"
[Harvest]
Scatter=no
```

How absolute the refusal is depends on what is being asked. A vehicle or a soldier is refused only when the request is not a forced one, and forcing is the common case rather than the exception: some three dozen call sites pass the forced flag, among them the player's own scatter order, a team's scatter mission, an object answering the shot that hit it, a crew or a survivor emerging from a wreck, and an object left standing on a building's footprint. A vehicle also has an earlier refusal that never reaches the flag at all — on the sleep, sticky and unload missions, and for a train whatever its mission, its routine returns before the flag is read. An aircraft has neither exemption: its scatter routine tests nothing but this flag, so a mission marked this way pins it completely.

One caller checks the mission itself rather than leaving the refusal to the routine. An object that has just been damaged and is *not* allowed to answer the attacker is offered a scatter only when its mission permits one, and that request is forced — so this is the one forced path the setting still stops.

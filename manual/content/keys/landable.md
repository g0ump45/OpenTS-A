---
key: Landable
summary: Makes an aircraft the player's to keep rather than a loaner it cannot select and that is allowed to leave the map.
see_also: ["Selectable", "Carryall", "Camera"]
when_omitted:
  kind: value
  value: "no"
---

Clearing the flag marks every instance of the type a loaner as it enters the map. [`Selectable=no`](/keys/selectable/#scope-aircrafttype) and a primary weapon carrying [`Camera=yes`](/keys/camera/) mark it the same way, and any one of the three is enough.

A loaner is on borrowed time and is handled accordingly. A player who can give it orders cannot select it — neither by clicking it nor by holding shift — so it stays outside that player's control while it flies. It is permitted to leave the map, which an ordinary object is not: a train, an object already on the retreat mission and a team on its way out are the only other exceptions. Once it is off, an aircraft with no target and no team is deleted. Going idle puts it on the retreat mission rather than into guard: carrying passengers it unloads first, and empty it takes the retreat mission. Running dry of ammunition puts it on the retreat mission as well, and it drops its target the moment it does. In a campaign it is also excused the rule that keeps a player's own aircraft out of shrouded cells.

Those retreat assignments are where it stops. An aircraft handles the retreat mission with a routine of its own, and that routine does nothing at all, so a loaner told to retreat picks no edge cell and flies nowhere; the permission to leave the map, and the deletion once it is off, apply only when something else carries it there.

Set the flag and none of that applies: the aircraft is selectable, may not leave the map, and answers going idle in the air by looking for a free bay among its [`Dock`](/keys/dock/) buildings to settle on, falling back to a nearby landing zone when it finds none.

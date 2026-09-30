---
key: AircraftFogReveal
summary: Radius in cells that an airborne aircraft with no sight of its own clears of fog.
see_also: ["system:map-visibility", Sight]
when_omitted:
  kind: value
  value: "6"
---

The value is reached only by an aircraft whose type sets [`Sight=0`](/keys/sight/), only while that aircraft is off the ground, and only while the game options switched fog of war on. Every other aircraft uses its own sight range and never consults this setting.

The pass it drives is not an ordinary reveal. It lifts fog from cells that are already out from under the shroud and leaves shrouded cells alone, so an aircraft of this kind clears the way ahead of it without ever uncovering new map. The height test that blocks a reveal behind high ground is applied only while the aircraft is below half the `[General]` [`FlightLevel`](/keys/flightlevel/) — the rules-wide figure, not the type's own key of that name; above that it clears every cell in the radius.

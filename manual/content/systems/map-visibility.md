---
title: Shroud, fog and the radar map
summary: "Keeps one shroud layer and one fog layer for the local player, and draws the radar map through the shroud."
category: maps-scenarios
keys:
  - AircraftFogReveal
  - AllowShroudedSubteranneanMoves
  - AllyReveal
  - AttackingAircraftSightRange
  - FlashFrameTime
  - FogRate
  - LeptonsPerSightIncrease
  - LocalSize
  - MoveToShroud
  - RadarCombatFlashTime
  - RadarOff
  - RadarOn
  - RevealByHeight
  - RevealTriggerRadius
  - ShroudGrow
  - ShroudRate
  - Sight
  - Size
  - VeteranSight
related:
  - type: system
    id: power
  - type: system
    id: cloaking
  - type: system
    id: ion-storms
  - type: system
    id: veterancy
  - type: system
    id: crates
  - type: enum
    id: RadarEventType
  - type: action
    id: TACTION_REVEAL_ALL
  - type: action
    id: TACTION_REVEAL_SOME
  - type: action
    id: TACTION_REVEAL_ZONE
  - type: action
    id: TACTION_CREEP_SHADOW
  - type: action
    id: TACTION_RESHROUD
  - type: mission
    id: TMISSION_REVEAL
  - type: mission
    id: TMISSION_RESHROUD
  - type: mission
    id: TMISSION_GOTO_SHROUD
  - type: command
    id: ToggleRadar
  - type: command
    id: CenterOnRadarEvent
---

Two covers hide terrain: the shroud, which every scenario starts with everywhere, and the fog of war, which only a skirmish or multiplayer lobby switches on. Both are held on the cells themselves, and both exist once.

:::caution[The shroud is not per-house knowledge]
A **look** is the scan an object takes of the cells around itself, lifting cover from each cell it reaches; the object taking it is the **looker**. Every look is filtered before it touches a cell, and one performed for a house other than the one at this machine does nothing at all unless it is first redirected to the local player. **Any of** these redirects it, in the order they are asked:

- a limpet drone of the local player's is riding the looker;
- the local player has spied the looking house's radar;
- the looking house is an ally of the local player and [`AllyReveal=yes`](/keys/allyreveal/) holds.

A computer house has no cover to see through and none to hide behind. What it knows is a flag on each object, not a map. The [Goto nearby shroud](/mapping/missions/tmission-goto-shroud/) team mission is written against that asymmetry: it sends its scouts toward cells that are shrouded for the local player.
:::

## Cell state

Each cell carries two independent pairs of states, one pair for the shroud and one for the fog. A cell is **mapped** when some part of it is out from under its cover, and **clear** when no piece of that cover is left over it at all. The partial piece drawn over a mapped cell is chosen from which of the eight neighbors are still unmapped, and a combination with no legal artwork is not allowed to occur: revealing one cell reveals any neighbor that would need such a piece, so one reveal can open several cells.

Every cell is built shrouded and fogged, and reading a scenario's `[Map]` [`Size`](/keys/size/) rebuilds them all in that state. That assignment declares the playfield: every cell the map has, with nothing outside it. Every map therefore begins fully dark. No setting opens a scenario revealed; a scenario that starts with the map uncovered does it with a trigger.

### Which cell a coordinate is tested against

Height is folded into every shroud and fog query. The coordinate's height in levels is halved and subtracted from both cell axes, so the answer comes from the cell the coordinate is drawn over rather than the one it stands on, and at an odd height the cell to the south-east is consulted as well. The same walk — every second height level from one upward, stepping one cell diagonally each time — is how a reveal finds the objects standing on high ground drawn at one spot, and how a fogged cell finds the structures to photograph.

## Revealing terrain

### Sight range

[`Sight=`](/keys/sight/) is a plain count of cells, not a lepton distance like a weapon's [`Range=`](/keys/range/). A type that leaves it at zero takes no ordinary look at all; only the aircraft path below does anything with a zero sight range.

Two multipliers are applied in order. Height comes first: an object gains 10 per cent for each whole [`LeptonsPerSightIncrease`](/keys/leptonspersightincrease/) leptons of elevation it carries. One height level is 104 leptons and the engine default is 50, so a whole level buys two increments — a unit one level up sees a fifth further, and one four levels up eighty per cent further. A rise in that bonus makes that same look a full scan rather than an incremental one. The `SIGHT` [veteran ability](/systems/veterancy/#abilities) then multiplies the widened figure through [`VeteranSight`](/keys/veteransight/).

:::caution[The result is capped at ten cells]
Whatever `Sight=`, the height bonus and the veteran multiplier produce, the scan clamps the radius to ten cells before it starts, because the ring tables it walks stop at ring ten. Any sight range above ten is spent.
:::

:::danger[A zero divisor crashes the look]
`LeptonsPerSightIncrease` is used as a divisor with no guard. `LeptonsPerSightIncrease=0` divides by zero on the next look any object takes.
:::

### The scan

The scan center is the cell the looker is drawn over, not the cell it occupies. A looker whose drawn cell lies outside the playfield reveals nothing at all. Candidates are then taken ring by ring out to the capped radius, and each one is kept only while it too lies inside the playfield and its straight-line distance from the center is within that radius, so the revealed area is a disc measured in cells. Both tests are against the playfield rather than the smaller playable area, so a look reaches cells in the map's border.

With [`RevealByHeight=yes`](/keys/revealbyheight/) each surviving candidate is tested once more. The engine probes a single cell — the candidate's ground cell, displaced two cells on both axes and then stepped once toward the center — and compares its ground height against the looker's own: the reveal goes through only while the probed ground stands no more than three height levels above the looker. That comparison against a single probed cell is the whole of the rule: the ground between the looker and the candidate is never examined, and the three levels are fixed in the engine.

:::caution[The incremental shortcut is unreachable at the default]
A look that knows the object moved only one cell can skip the inner rings, but the skip is guarded on `RevealByHeight=no`. At the default every look scans the full disc, however short the move was.
:::

### Who looks, and when

An object looks only once it has been locked to the playable area — the smaller region [`LocalSize`](/keys/localsize/) declares inside the playfield, which the engine clips and insets further. One that has never stood inside it reveals nothing, and the lock is re-evaluated for every object whenever that area changes. A house flagged as passive, such as the civilians, reveals only in a campaign.

- A vehicle or infantryman looks each time it reaches the center of a cell, incrementally unless its locomotor asked for a full look.
- An aircraft looks every fifteen frames while its house is allied to the local player, and ignores all of the above. It takes no lock test, no height bonus and no veteran multiplier; a landed aircraft sees exactly one cell whatever its type says. Only when its type sets `Sight=0` and fog of war is running does it fall through to [`AircraftFogReveal`](/keys/aircraftfogreveal/), which lifts fog without touching the shroud and applies the height test only while the aircraft is below half the `[General]` [`FlightLevel`](/keys/flightlevel/#scope-global-rules), the rules-wide figure rather than the type's own key of that name.
- An object takes a fresh look when it is unlimboed, when a transport sets it down, when it finishes a teleport, surfaces from a tunnel or lands from a jumpjet flight, when it arrives by drop pod, when a structure is captured by a player-controlled house, and when the player discovers it — an object of the player's own house in a campaign, any object outside one. The redirects above decide whose shroud that look lifts, so a stranger's object reveals nothing by being found, while a structure an ally places outside a campaign lifts the shroud around itself the moment it goes down.
- Terrain objects and animations never look; only vehicles, infantry, aircraft and structures do.

Several further paths reveal ground outside that cadence.

An object that fires reveals a hard-coded two cells around itself, granted to the target's owner rather than to its own house, while all of these hold:

- the target belongs to a player-controlled house;
- **Any of:**
  - **All of:** the firing object is not the local player's, and the player has not discovered it;
  - **All of:** it stands on shrouded or fogged ground, and it is not an aircraft of the local player's.

The first branch turns on the firer being an undiscovered stranger. The second turns on where it stands instead, and asks about ownership only to spare the local player's aircraft, so it reaches the player's own vehicles, infantry and structures as readily as anybody else's.

An aircraft of the local player's house that fires from or at shrouded ground reveals [`AttackingAircraftSightRange`](/keys/attackingaircraftsightrange/) cells around itself. Forming an alliance with the local player makes every object of the new ally take an ordinary look at once, while `AllyReveal=yes` holds; the lock test, the passive-house rule, the height bonus and the aircraft rule all apply, so a [passive house](/keys/multiplaypassive/) that allies outside a campaign reveals nothing. And a spy inside an enemy [`Radar=yes`](/keys/radar/) structure makes every object of the spied house take that same look at once, then leaves that house marked as spied, so its objects' own looks go on revealing ground for the local player for as long as that house keeps a spied radar structure. Destroying or capturing that structure recomputes the mark from scratch.

### Reveals granted outright

- [Reveal around waypoint...](/mapping/actions/taction-reveal-some/) reveals [`RevealTriggerRadius`](/keys/revealtriggerradius/) cells around a waypoint, with the height test on.
- [Reveal zone of waypoint...](/mapping/actions/taction-reveal-zone/) walks the playable area and reveals two cells around every cell sharing the waypoint's crusher [movement zone](/glossary/#movement-zone).
- [Reveal all map](/mapping/actions/taction-reveal-all/) reveals every cell of the playfield and marks the player as seeing everything, after which the two actions above do nothing.
- [Reveal map](/mapping/missions/tmission-reveal/) lifts the shroud alone, leaving the fog where it is, and is refused once the player already sees everything.
- The local player's own defeat outside coach mode, and an observer's seat, lift both covers from every cell and discard the fog stand-ins. [Observers and coach mode](/systems/observers/) owns that view; under coach mode defeat changes nothing.
- The reveal and darkness crate results are owned by [crates](/systems/crates/#results-that-reach-the-whole-map).

## The fog of war

Fog is a lobby option outside a campaign and a map setting inside one. A campaign clears the flag before the scenario file is read, after which the map's [`FogOfWar=yes`](/keys/fogofwar/) is the only thing that can set it again; a skirmish or network game takes it from the game options and ignores the map. Either way, when it is on the fog is raised over every cell at the end of scenario loading. While it is running the shroud is drawn with the fog artwork rather than its own, so both covers match.

A cell passing under the fog photographs what stands on it. A structure whose every footprint cell is fogged leaves a stand-in attached to each of those cells and keeps being drawn from it; a vehicle, infantryman or aircraft leaves nothing at all and is merely deselected, so mobile objects simply vanish. Lifting the fog throws the stand-ins away, unhooking a multi-cell one from every cell it was attached to first.

The two covers are not symmetric. A shroud reveal always lifts the fog from the same cell, but an unfog pass only touches cells that are already out of the shroud, so nothing that lifts fog can ever lift shroud.

A player who has been given the whole map — an observer, or a defeated player outside coach mode — is told that nothing is fogged, and the fog pass is not drawn for them at all.

## Losing ground again

Neither pass below runs for a player who has been given the whole map; [observers and coach mode](/systems/observers/) says who that is.

### Shroud regrowth

While [`ShroudGrow=yes`](/keys/shroudgrow/) and [`ShroudRate`](/keys/shroudrate/) is not zero, a pass runs every `ShroudRate` game minutes. It marks only the fringe — cells that are mapped but still carry a partial shroud piece — shrouds each mark, and then has everything still watching the map look again. A cell well inside a revealed area is clear rather than merely mapped, so it never qualifies; the only cells that do are the one-cell ring where the partial pieces are drawn. That is why the shroud creeps inward exactly one cell per pass and never reappears in the middle of a revealed area. The timer starts at zero, so the first eligible frame runs a pass immediately and the interval spaces only the passes after it. [Creep shadow back in](/mapping/actions/taction-creep-shadow/) runs the same pass on demand, whatever the two settings say.

### Fog regrowth

While fog of war is running and [`FogRate`](/keys/fograte/) is not zero, the matching pass runs every `FogRate` game minutes with the same first-frame behavior. It marks the fog fringe, then has every object look in a mode that clears the mark without revealing anything, and fogs whatever mark survives. That is how the pass asks which cells are still being watched.

:::caution[An allied building reveals ground during the fog pass]
The sweep sends the local player's own objects through the mark-clearing look, but an ally's structure takes the ordinary branch instead and maps the cells it can see. With `AllyReveal=yes`, every fog pass therefore hands the player fresh terrain around each allied structure.
:::

### Re-shrouding everything

[Reshroud map](/mapping/actions/taction-reshroud/) and its [team mission](/mapping/missions/tmission-reshroud/) clear both covers' states on every cell, have everything still watching look again, and clear the mark that says the player sees everything — which is what lets the reveal actions work once more.

## The radar map

### What it draws

The background picture is built by asking every cell for its own terrain colors, taken in a fixed order: a terrain object's radar color, then the bridge color for a cell lying under one, then a non-Tiberium overlay's own radar color, then the color of Tiberium growing there, and otherwise the tile's stored low and high colors scaled by theater and lifted toward a brighter shade by the cell's height. Two entries are stored per cell, side by side, and the whole array is then scaled down into the pane.

Objects are drawn over that picture from a tracking table keyed on radar pixel. Each blip takes the owning house's color, disguised infantry take the local player's colors instead, and where several objects claim one pixel the first one found wins. An object in [limbo](/glossary/#limbo) is removed from that table and cannot be put back until it leaves limbo. A building whose pixel would fall outside the surface is not tracked at all; a mobile object in the same position is pulled back to the nearest edge pixel. Any damage that registers a result starts a flash timer of [`RadarCombatFlashTime`](/keys/radarcombatflashtime/) frames on the damaged object, but only an object of the local player's own house is repainted from it — every [`FlashFrameTime`](/keys/flashframetime/) frames, and drawn inverted on alternate beats. Which other objects reach the table is decided by the radar-visibility test owned by [cloaking and detection](/systems/cloaking/#on-the-radar).

A white rectangle marks the part of the map the tactical view is showing, and a white frame surrounds the pane. Radar events are drawn over everything else; [radar event](/reference/enums/radar-event/) covers the kinds and their timings.

### What it refuses to draw

:::caution[Nothing censors the picture itself]
No branch of the terrain color lookup consults the shroud, the fog or ownership, so the background image is a true-color picture of every cell of the playable area at all times. What hides it is a single test taken as each pixel is plotted: the engine asks whether the coordinate under that pixel is shrouded and writes black if it is. That per-pixel question is the entire terrain censorship the radar performs.
:::

Fog is never asked about for terrain. Fogged ground keeps its true color on the radar even while the tactical view shows nothing there; only objects drop out under fog.

Three further conditions govern the pane rather than the terrain. Nothing at all is drawn in the map editor. While the pane is opening or closing only the frame animation is drawn, forty frames at four system ticks each, with [`RadarOn`](/keys/radaron/) and [`RadarOff`](/keys/radaroff/) played as the change starts. And clicks on the pane are refused unless it is currently showing the tactical map. Whether the pane is raised at all is decided elsewhere: [power output and drain](/systems/power/#radar) covers the availability test, and [ion storms](/systems/ion-storms/#radar) the suppression that overrides it.

## What the other houses know

Discovery is per object, not per cell. One flag records that the local player has seen the object; a single second flag records that some house other than the player's has, shared by all of them and never cleared. Discovering an object of another house springs the [Discovered by player](/mapping/events/tevent-discovered/) event on its tag, and a discovered object takes a fresh look — one of the player's own in a campaign, any object outside one. The player's flag is given up again in two places: an object of a computer house loses it whenever it goes into [limbo](/glossary/#limbo), boarding a transport for instance, and any object unlimboed outside the playable area starts undiscovered. An object of a human house never gives it up that first way.

Campaign rules are stricter than the rest. Outside a campaign every object is revealed the moment it is placed on a cell and every structure the moment it is unlimboed. In a campaign a placed object waits for its cell to be free of both covers and a structure waits for its cell to be completely clear of shroud, every object is marked discovered as soon as its own coordinate is out from under the shroud, and a player-controlled house's threat evaluation skips an object of another house it has not discovered — an aircraft excepted.

The shroud also gates orders. An order onto a shrouded cell is refused unless the type is [`MoveToShroud=yes`](/keys/movetoshroud/) and the cell lies inside the playable area, and when it is allowed the order is reduced to a plain move, a patrol waypoint order excepted. Clicking a subterranean unit onto a shrouded object does nothing at all unless [`AllowShroudedSubteranneanMoves=yes`](/keys/allowshroudedsubteranneanmoves/); an aircraft is refused that way regardless.

:::caution[There is no gap generator or GPS reveal, and nothing jams the radar]
Three paths survive in the tree only as disabled code: the gap generator's cleanup, the block that would have jammed the radar or lifted it through a GPS reading, and the branch that made an aircraft's [`Camera=yes`](/keys/camera/) weapon photograph the ground instead of firing. None of it compiles into the game and nothing replaces it, so no structure, weapon or setting hides ground from an opponent; the map a scenario re-shrouds, it re-shrouds for the player at this machine. Only that weapon's reveal is dead, not the setting: the flag is still read as an aircraft enters the map, where it marks the aircraft a loaner.

Radar can be taken away, by stunning rather than by jamming. An [EM pulse](/systems/emp-pulse/) reaches every building inside its radius without asking who owns it, and a stunned [`Radar=yes`](/keys/radar/) structure stops supplying the radar map for as long as the stun lasts. [Power output and drain](/systems/power/#radar) owns that test.
:::

## Parsed settings without effect

[`BlendedFog`](/keys/blendedfog/) selects between two fog rendering paths inside the routine that draws terrain tiles, but both calls into that routine pass the fog parameter guarding them as false, so neither path is reachable. [`CameraRange`](/keys/camerarange/) is stored and read by nothing.

---
title: Movement and terrain
summary: "Settles which cells an object may step into and what fraction of its top speed it crosses each one at."
category: units-movement
keys:
  - Acceleration
  - AccelerationFactor
  - Accelerates
  - AllowBurrowing
  - AutoCrush
  - Buildable
  - Climb
  - CruiseHeight
  - Crushable
  - Crusher
  - DeaccelerationFactor
  - DeployToFire
  - FlightLevel
  - HoverBob
  - HoverDampen
  - IsDropship
  - IsTrain
  - Landable
  - Locomotor
  - MaxBlockCount
  - MovementRestrictedTo
  - MovementZone
  - PitchAngle
  - PitchSpeed
  - PlayerAutoCrush
  - ROT
  - RollAngle
  - SlowdownDistance
  - Speed
  - SpeedType
  - TiltsWhenCrushes
  - TooBigToFitUnderBridge
  - TrackedDownhill
  - TrackedUphill
  - TunnelSpeed
  - TurnRate
  - Weight
  - WheeledDownhill
  - WheeledUphill
  - WobbleDeviation
  - WobblesPerSecond
related:
  - type: enum
    id: LandType
  - type: enum
    id: SpeedType
  - type: enum
    id: MZoneType
  - type: internal
    id: locomotion
  - type: system
    id: walls-and-gates
  - type: system
    id: drop-pods
---

An object that will not go where it is sent and an object that arrives slower than its [`Speed=`](/keys/speed/) suggests are two different faults, and three mechanisms stand between the order and the moving object. A per-step test decides whether this object may enter that [cell](/glossary/#cell) at all. A map-wide grouping decides whether the destination is reachable before a route is attempted. A throttle decides what fraction of the type's top speed the object crosses at. Four things feed those three: one table in the rules files, and the type's [`SpeedType`](/keys/speedtype/), [`MovementZone`](/keys/movementzone/) and [`Locomotor`](/keys/locomotor/).

The four are routinely mistaken for one another. `SpeedType` picks a column of the terrain table and reaches both the per-step test and the throttle. `MovementZone` reaches the grouping and nothing else. The locomotor decides how the object travels and, for all but one of the ten, has no say in the terrain figures or the per-step test. Setting one without the others is the usual reason a change appears to do nothing.

## The terrain table

Twelve `rules.ini` sections carry the whole of it, one per [land type](/reference/enums/land-type/): `[Clear]`, `[Road]`, `[Water]`, `[Rock]`, `[Wall]`, `[Tiberium]`, `[Beach]`, `[Rough]`, `[Ice]`, `[Railroad]`, `[Tunnel]` and `[Weeds]`. Each holds one figure per [speed type](/reference/enums/speed-type/) — `Foot=`, `Track=`, `Wheel=`, `Hover=`, `Winged=`, `Float=`, `Amphibious=` and `Creep=` — with [`Buildable=`](/keys/buildable/) beside them. Ninety-six figures in all, and the engine supplies none of them.

A land type whose section appears in no file is passed over entirely: the section heading is what admits the reads, and a land type nothing declares keeps a figure of zero for every speed type and a cleared buildable flag. Zero is the impassable marker rather than a slow one, so removing `[Rough]` does not make rough ground quick — it closes rough ground to everything that walks, drives, hovers or floats. Where the section is present, all nine reads run, each defaulting to the figure already in force, so a later file or a map may override one entry without disturbing its neighbors. A figure above `1` is cut to `1` as it is read; nothing clamps the bottom of the range.

Every one of the ninety-six is read twice over, in opposite directions:

- **Exactly zero** means the cell is refused. This is the reading that decides passability, and it is the only reading infantry, hovercraft, mechs, tunnelers and aircraft ever get.
- **Anything else** is a fraction of full speed, where `1` is full speed and smaller is slower. Only a vehicle moved by the drive locomotor is throttled by it.

```ini title="rules.ini"
[Water]
Foot=0%
Track=0%
Wheel=0%
Hover=100%
Amphibious=80%
Buildable=no

[MYSKIMMER] ; a UnitType registered in [VehicleTypes]
SpeedType=Hover
MovementZone=AmphibiousCrusher
Locomotor={4A582742-9839-11D1-B709-00A024DDAFD1} ; hover
```

Nothing that governs flight reads the `Winged` column. An aircraft's cell test is answered before the table is reached, and the sections the game ships carry no `Winged=` line at all, which leaves that column at zero for all twelve land types. A vehicle given `SpeedType=Winged` is therefore refused every cell on the map until a rules file writes the column in.

## Why a cell refuses a vehicle

The tests run in the order below, and which one a vehicle stops at is usually the whole explanation. Only some of them end the question; the rest raise a price instead.

1. **The land type restriction.** [`MovementRestrictedTo=`](/keys/movementrestrictedto/) refuses every cell whose land type is not the one named, before anything else is looked at.
2. **Tunnel geometry.** A cell holding a tunnel is refused when the vehicle is entering it more than a quarter turn off the tunnel's own facing, and again when the cell it is leaving holds one on the same terms — which is what stops a vehicle crossing a tunnel mouth sideways.
3. **The height step.** Covered [below](#height-ramps-and-bridges), and the most common flat refusal on a hand-built map.
4. **The map edge.** A cell outside the playable area is refused unless the vehicle is one of the few [allowed to leave the map](/keys/landable/).
5. **The locomotor's own say.** Nine of the ten locomotors accept every cell. The tunnel locomotor is the exception, refusing every cell a subterranean object may not [burrow through](/keys/allowburrowing/).
6. **Overlay.** A wall overlay is refused outright unless the vehicle is a [`Crusher=yes`](/keys/crusher/) one and the wall [`Crushable=yes`](/keys/crushable/), or it carries a warhead that brings walls down; [walls in combat and movement](/systems/walls-and-gates/#walls-in-combat-and-movement) owns the pairings. A crate is refused to a computer-controlled vehicle in a campaign.
7. **What is standing there.** Buildings, gates, allied objects moving and stationary, enemy objects, crushable objects and cloaked objects each contribute a verdict of their own, subject to a long list of exemptions — a transport the vehicle is boarding, a repair bay it is entering, a refinery bib it is docking at, an invisible or limpet-mine structure, an open laser fence, an inactive firestorm wall. A terrain object is destroyable only where the selected weapon carries [`Wood=yes`](/keys/wood/) and the terrain type is not [`Immune=yes`](/keys/immune/#scope-aircrafttype); otherwise it is strictly impassable.
8. **The terrain figure.** The `SpeedType` column of the destination's land type, refused only where it reads exactly zero. This test sits near the end, not the beginning.
9. **Reservations.** A cell another object has already claimed for its own next step is treated as blocked by something moving; an enemy infantry reservation is destroyable to an armed vehicle and refused to an unarmed one that cannot crush.

One vehicle is exempt from most of this. An [`IsTrain=yes`](/keys/istrain/) car treats every obstruction short of the strictly prohibited as a clear cell, so only the tests that refuse outright still stop it.

Otherwise the answer is not yes or no. Eight verdicts are possible, and the test keeps the most severe one it meets: clear, a cloaked enemy, something moving through, a closed friendly gate, a friendly obstruction that could be destroyed, an enemy obstruction that could be destroyed, a friendly object temporarily in the way, and strictly prohibited. Only the last keeps a route out of the cell; every other verdict is a [path cost](/glossary/#path-cost) the search pays and moves on. That is why a vehicle sent through a wall it can shoot goes and shoots it rather than routing around it.

A cell spanned by a bridge is two places. It is asked about at the deck's height or at the ground beneath it, and the terrain figure is skipped entirely for the deck — which is how a tracked vehicle whose `[Water] Track=` reads `0` crosses a river. At ground level under that same bridge it is refused exactly as it would be in the open.

### Height, ramps and bridges

Before terrain or occupancy is weighed, the step between the two cells is measured. A **ramp** here is a sloped tile, the artwork that carries ground from one height level to the next.

- **Level ground.** Allowed.
- **One level apart.** Allowed only across a ramp, and the ramp must be the cell at the lower of the two heights: climbing, the cell being left; descending, the cell being entered.
- **Four levels apart.** The bridge case. Allowed only where the cell beneath the deck is marked as spanned and the span is one that may be traveled.
- **Anything else.** Refused.

Nothing grants an exception. A cliff two levels high stops every ground object whatever its land type is priced at, whatever its movement zone accepts and whatever locomotor it uses.

### Infantry and aircraft answer differently

Infantry run the same shape of test with four differences. They have no land type restriction, and their test never asks the locomotor at all, so an infantryman moved by the tunnel locomotor is not held to the burrowing test the way a vehicle is. A wall whose damage stage has reached its last is a hole they walk through with nothing else consulted. Every Tiberium overlay family follows the cell's land type and the `Foot` figure like any other non-wall overlay; no image-number range is refused separately. The terrain figure is skipped while an infantryman is tethered to something — boarding a transport, capturing a structure — so an engineer may finish a capture on ground its own column prices at zero.

An aircraft's test reads no terrain at all. Its speed type is winged, which the cell test answers as clear before looking at anything else, so one condition remains: a player's own aircraft that is not a [loaner](/keys/landable/) is refused a shrouded cell in a campaign. Height, walls, cliffs, water and occupancy are invisible to it.

## The zone map

Reachability is judged before a route is attempted, against a grouping rebuilt whenever the ground changes. Every cell is boiled down to one **blockage rating** out of seven, each of the ten [movement zone](/reference/enums/movement-zone/) classes accepts or refuses each rating, and connected runs of accepted ground become that class's [movement zones](/glossary/#movement-zone).

The rating is settled in the order below, and the first line that fits wins. Nothing in it consults the object being moved, its speed type, or any column but `Wheel` — so one rating serves every class, and a land type that fails this test is out of the zone map for all of them at once.

| Rating | Set by |
| --- | --- |
| Outside | The cell lies outside the playable area |
| Crushable | The cell carries a [`Crushable=yes`](/keys/crushable/) overlay |
| Blocked | The cell carries a wall overlay, or a terrain object filling every one of its standing places |
| Impassable | The overlay's own land type prices `Wheel=` at exactly zero, or the cell's own land type at `0.01` or below, or an active firestorm wall stands there |
| Water | The land type is `Water` or `Beach`, whatever those sections say |
| Partly blocked | A terrain object stands there leaving some standing places free |
| Open land | Nothing above applied |

The `Wheel` fixation is the trap. A land type priced generously for `Track` or `Hover` and at zero for `Wheel` drops out of every class's zones, the classes that ought to cross it included. It is why a hovercraft needs a movement zone accepting water as well as a `[Water] Hover=` above zero: the two are read from different places and neither covers for the other. The two thresholds above differ as well, so a `Wheel=` figure of `0.005` is enterable by the per-step test and still leaves its land type out of every zone.

Which classes accept which rating is the whole of what a movement zone name means. The table below reads the other way round from the enum list, because the useful question is which classes a piece of ground is open to.

| Rating | Movement zones that accept it |
| --- | --- |
| Open land | All ten |
| Crushable | `Crusher`, `Destroyer`, `AmphibiousDestroyer`, `AmphibiousCrusher`, `Subterannean`, `InfantryDestroyer`, `Fly` |
| Blocked | `Destroyer`, `AmphibiousDestroyer`, `Subterannean`, `InfantryDestroyer`, `Fly` |
| Water | `Amphibious`, `AmphibiousCrusher`, `AmphibiousDestroyer`, `Fly` |
| Partly blocked | `Infantry`, `InfantryDestroyer`, `Fly` |
| Impassable | `Subterannean`, `Fly` |
| Outside | None |

Two readings off it are worth stating. `Normal`, `Amphibious` and `Infantry` all refuse crushable ground, so a plain amphibious vehicle routes around a sandbag wall exactly as an ordinary one does. And no class holds a zone outside the playable area, `Fly` included, so nothing has a route to ground beyond that boundary.

Height enters separately from the rating. A zone is filled one run of cells at a time, and each run is grown outward from its seed in two directions, every cell being compared against the one before it rather than against the seed. Two things follow. A slope climbing a single level per cell is never broken however high it eventually reaches, so a long ramp stays one zone from bottom to top. And the two directions do not stop at the same step: growing one way ends the run at a difference of two levels and growing the other at four, so the same boundary can fall inside a zone or between two according to which side the fill reached it from. A cliff exceeds both thresholds either way, which puts its top and the ground below it in different zones for every class at once. Bridges and tunnels are recorded as crossings and stitched across afterwards, which makes them the only joins between zones the terrain itself keeps apart.

## The route search prices no terrain

The route search adds up a [path cost](/glossary/#path-cost) and never prices terrain into it. It reaches the table only through the per-step test above, where zero means the cell cannot be entered and every other figure is a step like any other. A road and a patch of rough ground cost the search the same, so a route that follows roads is a coincidence of geometry rather than a preference. The terrain figures act afterwards, on the throttle.

What the search does price, and the settings beside it that are fixed where nothing can reach them, belong to [Route search](/systems/route-search/).

## Why it is slower than its Speed says

`Speed=` is a figure from `0` to `100`, and one above `100` is cut to `100` before it is scaled into the top speed the object keeps — so raising a fast type's `Speed=` past that ceiling changes nothing.

The table gives the whole chain for a driving vehicle in order. Steps 1 to 4 settle the **throttle** — a fraction from 0 to 1 that the locomotor writes as each step into a new cell begins, and the only part of the chain the ground reaches. Steps 5 to 9 turn that throttle into the distance covered, and are worked out afresh every frame.

| Step | Factor |
| --- | --- |
| 1 | The terrain figure for the destination cell's land type, capped at full speed |
| 2 | The slope multiplier, where the ground under the destination stands higher or lower than the ground under the vehicle |
| 3 | Three quarters, once the vehicle's health has fallen to the yellow condition |
| 4 | Either a fifth while the vehicle is crushing something, or the acceleration ramp — both only on an [`Accelerates=yes`](/keys/accelerates/) vehicle, and the crushing clamp taking precedence. [`TiltsWhenCrushes`](/keys/tiltswhencrushes/) changes only whether the hull lurches while it goes through |
| 5 | The type's top speed, cut by any limpet drone clamped to the vehicle |
| 6 | The owner's [ground speed bias](/systems/difficulty/#how-the-figures-are-combined), which folds together the country's, the difficulty slot's and the rules-wide one |
| 7 | The speed multiplier a [crate](/systems/crates/#results-that-sweep-a-radius) left on the object, which one crate sets and no later crate raises |
| 8 | Doubling from the [`FASTER` veteran ability](/systems/veterancy/#abilities), where the crew has earned it |
| 9 | Half, while the vehicle is carrying a captured flag |

Four details in that chain are easy to miss. A step of two or more height levels is costed from the `[Road]` row rather than from the destination's own land type, which is how a vehicle keeps its speed climbing onto a bridge deck over water. The slope multiplier is chosen by speed type alone — `Track` takes [`TrackedUphill`](/keys/trackeduphill/) and [`TrackedDownhill`](/keys/trackeddownhill/), and every other speed type on a vehicle takes [`WheeledUphill`](/keys/wheeleduphill/) and [`WheeledDownhill`](/keys/wheeleddownhill/) whatever its name suggests. A product of exactly zero is replaced with half speed rather than a stop. And steps 5 to 9 truncate to whole numbers after each multiplication, so a slow type loses proportionally more to each factor than a fast one does.

The damage penalty belongs to the drive locomotor alone: everything else on the map travels at the same speed damaged as undamaged.

## What each locomotor drives its speed from

[`Locomotor=`](/keys/locomotor/) names one of ten travel routines, and which one it is settles more about how a type moves than the rest of this page put together. The table gives where each takes its speed; the last column is the one to read first, because only one entry in it consults the terrain table at all.

| Locomotor | Speed comes from | Terrain figure |
| --- | --- | --- |
| Drive | The full chain above | Throttles it |
| Walk, Mech | The chain above at a fixed full throttle | Ignored |
| Hover | The same, times the locomotor's own acceleration ramp | Ignored |
| Tunnel | The same, times [`TunnelSpeed`](/keys/tunnelspeed/) going down and coming up; a fixed rate underground | Ignored |
| Fly | The type's top speed times its own throttle, and nothing else | Ignored |
| Jumpjet | `[JumpjetControls]` alone; the type's own `Speed=` is not read | Ignored |
| Levitate | `[LEVITATION]` alone; the type's own `Speed=` is not read | Ignored |
| Drop pod | Its height above the ground, floored at the rules-wide descent rate | Ignored |
| Teleport | Instantaneous | Ignored |

The fly locomotor's entry is worth reading twice: an aircraft's travel bypasses the ground speed bias, the crate multiplier, the veteran ability, the flag penalty and the damage penalty alike. The setting meant to give aircraft a bias of their own is stored and never read, which [difficulty settings](/systems/difficulty/#parsed-settings-without-effect) covers.

The rest of the cluster divides the same way, each setting reaching one locomotor: [`Accelerates`](/keys/accelerates/), [`AccelerationFactor`](/keys/accelerationfactor/), [`DeaccelerationFactor`](/keys/deaccelerationfactor/) and the slope multipliers the drive locomotor; [`PitchAngle`](/keys/pitchangle/), [`PitchSpeed`](/keys/pitchspeed/), [`RollAngle`](/keys/rollangle/), [`FlightLevel`](/keys/flightlevel/) and [`IsDropship`](/keys/isdropship/) the fly locomotor; [`HoverBob`](/keys/hoverbob/) and [`HoverDampen`](/keys/hoverdampen/) the hover and levitate locomotors together; [`AllowBurrowing`](/keys/allowburrowing/) and [`TunnelSpeed`](/keys/tunnelspeed/) the tunnel locomotor. [`SlowdownDistance`](/keys/slowdowndistance/) is the one read by two, the fly and the drive. [`Climb`](/keys/climb/), [`CruiseHeight`](/keys/cruiseheight/), [`WobbleDeviation`](/keys/wobbledeviation/), [`WobblesPerSecond`](/keys/wobblespersecond/), [`TurnRate`](/keys/turnrate/) and [`Acceleration`](/keys/acceleration/) belong to no type at all: all six are written once in the shared `[JumpjetControls]` section.

[`ROT`](/keys/rot/) is read differently again. A mech stands still until its turn is finished, and so does a turretless driving vehicle; one carrying a turret keeps moving through the turn. A hovercraft is given twice its written figure and steers a drive direction separately from the facing it is drawn at, which is why it slews rather than turns. Infantry are created on a fixed maximum rate rather than the figure written on their type, and pick that figure up the first time they are healed.

A running object can be moved by a locomotor other than the one its type names — a tunneler leaving a war factory, a passenger falling in a drop pod, a jump jet infantryman on the ground. [Locomotion and piggybacking](/internals/locomotion/) covers the swap.

## Settings that reach no decision

Four of the cluster are parsed and never act on movement. [`MaxBlockCount`](/keys/maxblockcount/) keeps a tally of consecutive blocked frames that nothing turns on. [`PlayerAutoCrush`](/keys/playerautocrush/) is settled by a test that has already excluded every case it could apply to, and the per-type [`AutoCrush`](/keys/autocrush/) has no live reader either. [`TooBigToFitUnderBridge`](/keys/toobigtofitunderbridge/) reads as a movement restriction and is not one: it changes how a vehicle's image is sorted against a bridge deck, and neither restricts movement nor keeps a vehicle off a bridge cell.

[`Weight`](/keys/weight/) and [`DeployToFire`](/keys/deploytofire/) reach decisions, but not this one: the first governs how far a blast rocks a voxel object and whether a vehicle breaks the ice beneath it, the second where a vehicle may shoot from, through the [`Buildable=`](/keys/buildable/) flag in each land type's section.

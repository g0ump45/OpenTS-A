---
title: Building animations
summary: "Steps a structure's own artwork through five frame sequences and runs up to thirteen separate animations pinned to it, one per slot."
category: buildings-economy
keys:
  - ActiveAnim
  - ActiveAnimDamaged
  - ActiveAnimX
  - ActiveAnimY
  - ActiveAnimZAdjust
  - ActiveAnimYSort
  - ActiveAnimPowered
  - ActiveAnimPoweredLight
  - ActiveAnimTwo
  - ActiveAnimTwoDamaged
  - ActiveAnimTwoX
  - ActiveAnimTwoY
  - ActiveAnimTwoZAdjust
  - ActiveAnimTwoYSort
  - ActiveAnimTwoPowered
  - ActiveAnimTwoPoweredLight
  - ActiveAnimThree
  - ActiveAnimThreeDamaged
  - ActiveAnimThreeX
  - ActiveAnimThreeY
  - ActiveAnimThreeZAdjust
  - ActiveAnimThreeYSort
  - ActiveAnimThreePowered
  - ActiveAnimThreePoweredLight
  - ActiveAnimFour
  - ActiveAnimFourDamaged
  - ActiveAnimFourX
  - ActiveAnimFourY
  - ActiveAnimFourZAdjust
  - ActiveAnimFourYSort
  - ActiveAnimFourPowered
  - ActiveAnimFourPoweredLight
  - SpecialAnim
  - SpecialAnimDamaged
  - SpecialAnimX
  - SpecialAnimY
  - SpecialAnimZAdjust
  - SpecialAnimYSort
  - SpecialAnimPowered
  - SpecialAnimPoweredLight
  - SpecialAnimTwo
  - SpecialAnimTwoDamaged
  - SpecialAnimTwoX
  - SpecialAnimTwoY
  - SpecialAnimTwoZAdjust
  - SpecialAnimTwoYSort
  - SpecialAnimTwoPowered
  - SpecialAnimTwoPoweredLight
  - SpecialAnimThree
  - SpecialAnimThreeDamaged
  - SpecialAnimThreeX
  - SpecialAnimThreeY
  - SpecialAnimThreeZAdjust
  - SpecialAnimThreeYSort
  - SpecialAnimThreePowered
  - SpecialAnimThreePoweredLight
  - ProductionAnim
  - ProductionAnimDamaged
  - ProductionAnimX
  - ProductionAnimY
  - ProductionAnimZAdjust
  - ProductionAnimYSort
  - PreProductionAnim
  - PreProductionAnimDamaged
  - PreProductionAnimX
  - PreProductionAnimY
  - PreProductionAnimZAdjust
  - PreProductionAnimYSort
  - TurretAnim
  - TurretAnimDamaged
  - TurretAnimX
  - TurretAnimY
  - TurretAnimZAdjust
  - TurretAnimYSort
  - TurretAnimIsVoxel
  - TurretAnimIsExclusive
  - TurretChargeAnimRate
  - ChargeAnim
  - TeslaCharge
  - TeslaZap
  - Upgrades
  - AnimIdle
  - AnimActive
  - AnimAux1
  - AnimAux2
  - ExtraDamageStage
  - DeployingAnim
  - DoorAnim
  - DoorStages
  - DamagedDoor
  - UnderDoorAnim
  - Bib
  - BibShape
  - SensorArray
  - UnitRepair
  - SiloDamage
  - FirestormWall
  - Surface
  - YSortAdjust
related:
  - type: system
    id: power
  - type: system
    id: repair
  - type: system
    id: production
  - type: system
    id: laser-fences
  - type: system
    id: emp-pulse
  - type: system
    id: cloaking
  - type: format
    id: shp
---

A structure moves on screen through two mechanisms that share almost nothing. Its own artwork carries frames, and a small state machine steps through them. Separately, a structure runs up to thirteen **attached animations** — independent animation objects, each named in `[Animations]`, pinned to a point on the structure's artwork, cycling on their own timing, and created and destroyed as the structure changes state. The second is most of this page.

Each attached animation lives in a **slot**. A BuildingType declares one set of settings per slot, a structure holds at most one animation in each at a time, and each slot is filled and emptied by its own events. A slot no event ever reaches still stores every setting written for it and creates nothing from them.

## The thirteen slots

The table lists every slot with the assignment that names its animation and the moment something puts one there. Take the last column as a pointer: the mechanism below governs how any slot's animation is built, while the timing belongs to the setting that names it.

| Slot | Named by | Filled when |
| --- | --- | --- |
| Upgrade one, two, three | `PowerUp1Anim=`, `PowerUp2Anim=`, `PowerUp3Anim=`, each with a `PowerUp<n>DamagedAnim=`, `PowerUp<n>LocXX=`, `PowerUp<n>LocYY=`, `PowerUp<n>LocZZ=` and `PowerUp<n>YSort=` beside it | The first, second and third [`Upgrades=`](/keys/upgrades/) plug is installed. Removing a plug empties its slot |
| Active one to four | [`ActiveAnim=`](/keys/activeanim/), [`ActiveAnimTwo=`](/keys/activeanimtwo/), [`ActiveAnimThree=`](/keys/activeanimthree/), [`ActiveAnimFour=`](/keys/activeanimfour/) | The structure comes online, either as construction finishes or as the scenario places it |
| Pre-production | [`PreProductionAnim=`](/keys/preproductionanim/) | Work is being set up on the structure |
| Production | [`ProductionAnim=`](/keys/productionanim/) | The structure's work is in progress |
| Turret | [`TurretAnim=`](/keys/turretanim/) | The structure comes online, or its charge-up begins |
| Special one to three | [`SpecialAnim=`](/keys/specialanim/), [`SpecialAnimTwo=`](/keys/specialanimtwo/), [`SpecialAnimThree=`](/keys/specialanimthree/) | An event on a [`UnitRepair=yes`](/keys/unitrepair/), [`SiloDamage=yes`](/keys/silodamage/) or [`FirestormWall=yes`](/keys/firestormwall/) structure |

Two of the active slots carry behavior the other two do not. On a [`SensorArray=yes`](/keys/sensorarray/) structure, slot one starts two seconds — 30 frames — after construction finishes; every other path that starts slot one, and every path that starts the other three, applies no delay. Slot one is also the slot a [`UnitRepair=yes`](/keys/unitrepair/) bay stops while it services a vehicle, and slot two the one a [`TurretAnimIsExclusive=yes`](/keys/turretanimisexclusive/) turret displaces while it charges.

The turret slot is the one slot whose animation does not run on its own timing: its frame is set every pass from the structure's facing, or from a charge counter stepped at [`TurretChargeAnimRate`](/keys/turretchargeanimrate/) on a [`ChargeAnim=yes`](/keys/chargeanim/) structure. [`TeslaCharge`](/keys/teslacharge/) sounds as that wind-up begins; [`TeslaZap`](/keys/teslazap/) sounds nowhere.

## Building and emptying a slot

Whatever the occasion, one routine fills a slot. It takes the slot's healthy or damaged name and stops there if that name is empty; otherwise it looks the name up in `[Animations]` and creates an animation at the structure's drawing position, offset by the slot's `…X` and `…Y` and carrying its two draw-order biases. A name no `[Animations]` entry registers gets as far as the lookup and no further: nothing is created and the slot stays as it was, though the damage-state flag below has already moved by then. Filling a slot that already holds an animation replaces it and hands the new one the stage the old had reached, so the swap does not show as a jump.

One path bypasses the slot's names. The lettered turret variants a wall tower cycles through are built from the structure's Image ID with `_B`, `_C` or `_D` appended, and take the turret slot's offset and biases but not its name.

A slot empties in three ways: its animation plays to its end, something stops it deliberately, or the structure is taken off the map, which stops all thirteen at once. The first is why a looping animation holds its slot for the rest of the structure's life while a finite one leaves it free.

A running animation belongs to the structure rather than to the cell. Placing the structure down re-applies every slot's offset from the new position, and the structure's redraw pass brings its animations to the brightness and translucency it is drawn at, so one fading into a cloaking field takes them with it. Fog reaches them the same way: a structure passing under fog marks each of its animations fogged, an animation created on an already fogged structure is marked as it is created, and one whose AnimType leaves [`ShouldFogRemove`](/keys/shouldfogremove/) at its default is not drawn while that mark is set. Uncovering the structure clears it.

## The damaged form

Each slot carries a second name for its damaged form, and which of the two is used is fixed as the animation is created, from whether the structure has fallen to [`ConditionYellow`](/keys/conditionyellow/) or below. A slot that names no damaged form is given its healthy name as the art file is read, so one name serves both states; a slot that names only a damaged form runs nothing while the structure is healthy.

A structure keeps one flag recording which form it is currently showing, and that flag is per structure rather than per slot. Creating any animation in a form different from the flag flips it and restarts **every** animation the structure is running in the new form. Crossing `ConditionYellow` in either direction does the same directly, so a structure that takes a hit past the threshold swaps its whole set at once.

The consequence worth planning around runs the other way. Any slot started in the healthy form drags the rest of them back to healthy whether or not the structure is damaged, and they stay there until the next damage step or repair step re-tests the threshold. [A repair bay's animations](/keys/specialanim/#a-service-depot) and [three of the four production moments](/keys/productionanim/) each do this.

## Placement and draw order

`…X` and `…Y` offset the animation from the point the structure is drawn at, in screen pixels: `…X` to the right, `…Y` down the screen. The offset pins the animation to a point on the artwork rather than to a cell.

`…ZAdjust` and `…YSort` both decide what the animation ends up drawn over, through two different mechanisms.

- `…ZAdjust` biases the depth value the animation's pixels are tested against. A negative figure brings the animation toward the viewer, so it covers the structure and anything else at that depth; a positive figure pushes it away, so the structure covers it.
- `…YSort` is added to the animation's sorting position, in leptons, of which a [cell](/glossary/#cell) is 256. That position orders the ground layer, which is sorted once a frame. An AnimType left at the default [`Surface=no`](/keys/surface/) goes into the air layer instead, which is never sorted, so the bias reaches nothing there.

:::caution[The slot overrides the animation's own sort bias]
An AnimType may carry its own [`YSortAdjust=`](/keys/ysortadjust/), but a slot writes its figure over that as the animation is created, including the zero it holds when `…YSort` is omitted. An animation used both on its own and in a building slot keeps its bias in the first case and loses it in the second unless the slot repeats the value.
:::

:::caution[Both biases are held in a single byte]
`…ZAdjust` and `…YSort` are each stored in one signed byte. A figure from -128 through 127 is kept as written; anything outside that range wraps into it, so `…ZAdjust=200` is stored as -56 and pulls the animation in front of the structure it was meant to hide behind. The same ceiling caps `…YSort` at rather less than half a cell in either direction.
:::

## Power

The two power flags are two responses to the same shortfall. `…Powered=yes` freezes the animation on its current frame while the house cannot meet its drain and resumes it at full power; the animation stays on screen throughout. `…PoweredLight=yes` instead destroys the animation on the shortfall and creates it again at full power.

Only one of the two is consulted. The pass over a house's structures tests `…Powered` first and reaches `…PoweredLight` only when that flag is `no`, so `…PoweredLight=yes` left beside the default `…Powered=yes` never does anything. That pass reaches all thirteen slots on every structure the house owns, which is the one route by which a structure carrying none of the three special-slot flags runs a special animation. [Fields, fences and lights](/systems/power/#fields-fences-and-lights) covers which structures a house-wide shortfall reaches and which it spares.

The power cursor, the [Turn off building](/mapping/actions/taction-turn-off-attached/) trigger action and an [EMP pulse](/systems/emp-pulse/) reach the freeze by a different route, stopping one structure's `…Powered=yes` animations directly rather than through the house-wide pass. A `…PoweredLight=yes` animation keeps running through all three.

## Where each setting is read from

Only the first 15 characters of an animation name are kept, and where a slot's settings are read from is not uniform. The table gives the entry each half of a slot is taken from; the split shows only on a structure that borrows another's artwork, where the two entries are different sections.

| Slot | Names | Offset, biases and power flags |
| --- | --- | --- |
| Active one to four | The Image ID art entry | The Image ID art entry |
| Special, production and pre-production | The Image ID art entry | The art entry named after the ObjectType ID |
| Turret | The rules entry named after the ObjectType ID | The rules entry named after the ObjectType ID |

Everything but the turret slot reads its remaining settings only once the slot holds a name, healthy or damaged; on a structure that names neither, those settings are not read at all. The turret slot reads its four unconditionally.

## The upgrade slots and the active slots share one array

The thirteen slots are one array with the three upgrade slots at its head, and two paths walk into it by number rather than by name.

The art file is read one declared upgrade at a time — `PowerUp1Anim=` and its companions into the first slot, `PowerUp2Anim=` and its companions into the second — and the walk is bounded by [`Upgrades=`](/keys/upgrades/) rather than by the number of upgrade slots. A type declaring four upgrades therefore has its fourth plug's six art assignments read over the first active slot's two names, its offset and both of its biases, each field only where that plug's assignment is present. A fifth, sixth and seventh declared upgrade reach active slots two, three and four in turn.

:::danger[Installing a plug rewrites the host type's animation name]
Placing a plug copies the plug type's own Image ID into the host **type**'s slot for the upgrade level being installed, not into the structure that received it. Every structure of the host type shows that name in that slot from then on, including ones already standing and ones that never received a plug. The first three plugs write into upgrade slots, where that is the intended behavior; a fourth plug writes into the first active slot instead, and the host's `ActiveAnim=` is lost for the rest of the session.

The copy is made without a length check. A plug whose Image ID runs to sixteen characters or more is written into the sixteen-byte slot with no terminator, so the stored name runs on into the damaged name stored immediately after it.
:::

## The structure's own frames

The structure's own artwork has no slots in it. A structure is in one of five frame sequences at a time, four of them declared as a first frame, a frame count and a per-frame delay: [`AnimIdle`](/keys/animidle/) whenever nothing else has taken it over, [`AnimActive`](/keys/animactive/) while it is working, and [`AnimAux1`](/keys/animaux1/) and [`AnimAux2`](/keys/animaux2/) for the two further states a missile silo uses. The fifth is the construction sequence, which is not declared at all: its frame count is half the frame count of the [`Buildup=`](/keys/buildup/) file — or [`GateStages`](/keys/gatestages/) plus one on a gate — and its rate is that count divided into [`BuildupTime`](/keys/builduptime/). A [`Theater=yes`](/keys/theater/) structure is timed again as each theater is set up, over every frame in the file at a fixed five seconds, so neither the halving nor `BuildupTime` reaches it.

Damaged artwork is a second block of frames after the first, and where that block begins depends on which sequence the structure is in. A damaged structure in the idle sequence draws the very next frame after the one it would otherwise draw; in any of the other three it is offset by the largest end any of the four sequences reaches. [`ExtraDamageStage`](/keys/extradamagestage/) promises a third condition and reaches nothing.

Four further shapes are drawn around the structure rather than as part of it, and none is an attached animation: [`BibShape`](/keys/bibshape/) under it, [`DeployingAnim`](/keys/deployinganim/) in place of it while it unloads, and [`DoorAnim`](/keys/dooranim/) with [`UnderDoorAnim`](/keys/underdooranim/) around its factory door. Each is a shape file loaded with the rules and drawn from a frame the structure works out, so none cycles on its own. Despite the name, [`Bib=yes`](/keys/bib/) has nothing to do with the apron artwork: it opens the eastern edge of the footprint to vehicles and draws nothing.

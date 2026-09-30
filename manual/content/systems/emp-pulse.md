---
title: EMP pulse
summary: "Immobilizes objects inside a warhead-sized radius for a weapon-defined number of frames."
category: weapons-projectiles
keys:
  - Damage
  - EMEffect
  - EMPulseCannon
  - EMPulseSparkles
  - IsMobileEMP
  - MaxCharge
  - Spread
  - StartCharge
related:
  - type: action
    id: TACTION_DO_EXPLOSION
---

## Firing a pulse

A projectile whose warhead carries [`EMEffect=yes`](/keys/emeffect/) creates a pulse at its detonation cell instead of applying blast damage. Its radius in cells is the warhead's [`Spread`](/keys/spread/#scope-warheadtype), and its duration in game frames is the strength the projectile carries — the firing weapon's [`Damage`](/keys/damage/#scope-weapontype), scaled by the firer's firepower modifiers when the shot comes from ordinary combat.

:::caution[Damage is a duration, not damage]
Detonation branches on the warhead: an `EMEffect` warhead takes the branch that creates the pulse, so it never reaches the blast damage the other branch applies and the pulse costs no health. `Damage` is spent as the stun length in frames instead. A pulse also refuses to apply itself unless its duration still has a frame left to run, and it makes that test on the frame it is created, so `Damage=0` reaches nothing whatever: it stuns nobody, springs no trigger event, and is deleted on that same frame. `Spread` also shapes that warhead's damage falloff, so radius and falloff cannot be tuned apart.
:::

### EM Pulse Cannon superweapon

A superweapon declared [`Type=EMPulse`](/keys/type/) needs a launch site, and it takes the one nearest the target among the buildings that satisfy **all of**:

- it belongs to the firing house;
- it is out of [limbo](/glossary/#limbo);
- its type carries [`EMPulseCannon=yes`](/keys/empulsecannon/);
- it is powered on.

That building takes the missile mission and the target becomes the house's only pulse destination, so a second launch retargets a sequence in flight. With no eligible building the launch does nothing and the superweapon still discharges. The cursor reports the shot in range only while the player owns a powered cannon and the target lies inside that weapon's [`Range`](/keys/range/).

The cannon creates the hard-coded `PULSBALL` animation at its firing coordinate, waits 32 frames, then fires its primary weapon; the pulse comes from that weapon's own warhead, and [`EMPulseWarhead`](/keys/empulsewarhead/) and [`EMPulseProjectile`](/keys/empulseprojectile/) in `[SpecialWeapons]` are read into the rules and never consulted.

### Mobile EMP vehicle

A UnitType with [`IsMobileEMP=yes`](/keys/ismobileemp/) gains one charge point per frame while it is not immobilized, from [`StartCharge`](/keys/startcharge/) up to [`MaxCharge`](/keys/maxcharge/); the deploy cursor is refused below full charge. Deploying detonates a projectile of the hard-coded weapon `MobileEMPulseWeapon` at the vehicle's own position and resets the charge to zero.

### Scripted explosion

The [Do Explosion At](/mapping/actions/taction-do-explosion/) trigger action applies its weapon's ordinary blast damage, then creates a pulse from that warhead's `Spread` and that weapon's `Damage` when the weapon's ID matches the hard-coded name `empulseweapon` in any letter case. No source is recorded.

## What a pulse reaches

The pulse applies itself once, at creation; it never grows and never re-scans, so an object entering the circle afterwards is unaffected.

Aircraft are handled first, in a pass of their own. That pass takes an aircraft under **all of**:

- it is placed down on the map and out of limbo;
- its strength is above zero;
- it is less than one height level above the ground;
- the distance from its center to the center of the pulse's cell is under `Spread` cells.

Such an aircraft springs the [Paralyzed](/mapping/events/tevent-paralyzed/) event on its tag and is then put through the crash path, which acts only above zero height. The two heights are a window rather than a contradiction. An aircraft between the ground and one height level — one taking off, or settling onto a pad — springs the event and then crashes, which zeroes its strength, credits the kill to the firer, and kills its cargo. An aircraft at exactly zero height springs the event and the crash path returns having done nothing, but it is standing in its cell like any ground object, so the cell sweep below reaches it a second time and stuns it there.

An aircraft a full height level or more above the ground is reached by nothing at all. The aircraft pass has already excluded it, and the cell sweep below cannot see it either: an aircraft off the deck is drawn in the top layer and is entered in no cell's occupancy. A pulse under a flight of aircraft leaves them flying.

Anything actually tunneling inside the radius — a tunnel-locomotor object is only underground while it is burrowing, and stands in its cell like anything else at either end of the trip — is stunned next. The pulse's three range tests are not one test: the aircraft pass above measures a distance, while this pass and the cell sweep after it compare whole-cell offsets, and those two part at the boundary. The underground pass takes a cell strictly inside the radius; the cell sweep takes one at exactly `Spread` cells as well, so it reaches a ring the underground pass leaves alone. That sweep covers every valid cell it takes:

- **Buildings** register only on the cell holding their center. An [`InvisibleInGame=yes`](/keys/invisibleingame/) building is skipped, a limpet mine is destroyed outright with the firer credited, and a building whose type is [`IsCoreDefender=yes`](/keys/iscoredefender/#scope-buildingtype) springs its trigger without being stunned. Every other building is powered off, stunned, and — when its type is [one of the deployed-vehicle kinds](/keys/deploysinto/), the eight marks that make a structure the deployed form of a vehicle — given an [`EMPulseSparkles`](/keys/empulsesparkles/) animation.
- **Ground objects** in a cell that holds no building are stunned while **all of**:
  - **Any of:**
    - **All of:** it is a vehicle or an aircraft, it carries a locomotor, its type is not [`IsCoreDefender=yes`](/keys/iscoredefender/#scope-unittype) — a term the engine reaches through a vehicle alone, so an aircraft never consults it — and it is not the object that fired the pulse;
    - it is an infantryman whose type is a cyborg;
  - it is not a large or small visceroid.

A core-defender vehicle still springs the paralyzed event, which is the one thing it is given in place of the stun. A visceroid, and the vehicle or aircraft that fired the pulse, are passed over without one.

:::caution[Non-cyborg infantry are never affected]
The cell sweep stuns an infantryman only when the type is a cyborg. Ordinary infantry pass through a pulse untouched.
:::

:::caution[A building is tested on one cell only]
Only the cell holding a building's center is compared against the radius. A structure whose footprint overlaps the circle is untouched when its center cell lies outside it.
:::

A stunned object cannot move, and cannot fire unless it is a visceroid; it uncloaks and cannot recloak without the cloak ability or cloaking cover, and deploy orders are refused except for a building that may always undeploy. A stunned building reports itself unpowered, refuses to be switched back on, drops radar coverage for the player's house, and cannot serve as a launch site. House power output and drain are read from each building's player-set on/off state, which a pulse never changes, so a stunned power plant keeps feeding the grid at its normal output.

## Recovery

The pulse is removed once its duration elapses, and its removal touches no object. Each caught object counts its own stun down and recovers on the frame it reaches zero: a building powers back on and refreshes radar coverage, a vehicle, infantryman or aircraft powers its locomotor back on, and a harvester that is not unloading returns to harvesting.

---
key: IsFlamingGuy
summary: Runs the animation toward the nearest water and then plays it out where it stops.
see_also: ["RunningFrames", "FlamingInfantry", "SplashList"]
when_omitted:
  kind: value
  value: "no"
---

The animation is driven by a routine of its own instead of by the ordinary frame timing, and it is put through the object logic as well, so it falls off bridges and cliff edges like anything else that has height.

## Running

Each step, the animation looks over a ten by ten block of cells around itself for the nearest water inside the playable area and heads for it, moving 18 leptons a frame. Where no water is in reach it takes any neighboring cell it can still enter, chosen from a random starting direction, so a burning man boxed in by rock, walls, tunnels, buildings or vehicles has nowhere left to go. The run ends after seven cells, on arriving at water, or on running out of anywhere to go.

The frame shown while running is picked from the eight facings by the direction of travel, [`RunningFrames`](/keys/runningframes/) frames to each facing, cycling one frame every three of the game clock.

## Ending

The animation jumps to the frame just past the run cycle — `RunningFrames` times eight, plus one — and plays forward from there at one frame per game frame until it reaches the frame before the middle of its artwork, then removes itself. Landing from a fall ends the run on the spot, and a fall that ends in water adds the first splash of the rules' [`SplashList`](/keys/splashlist/).

## Artwork

The shape file is two parallel halves. The first holds the eight run cycles followed by the death sequence; the second holds the matching shadow frames, drawn darkened on the ground beneath whichever frame of the first half is showing. The shadow is omitted while the animation is falling.

:::danger[A burning man that can move stops the game]
The frame to show is worked out with a division by [`RunningFrames`](/keys/runningframes/), which is `0` unless the section sets it. An animation carrying this flag without running frames faults as soon as it takes its first step, so the game stops the moment one is created anywhere it can move.
:::

:::caution[The colors are the local player's, not the victim's]
The animation the rules name as [`FlamingInfantry`](/keys/flaminginfantry/) is drawn through the local player's color scheme rather than through the house of the man who was burned, so the same casualty looks different on every machine in a multiplayer game. Restoring a saved game applies that scheme to every animation carrying this flag, whichever way it was created.
:::

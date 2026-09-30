---
key: HunterSeekerDescendProximity
summary: Horizontal distance from its destination, in leptons, at which a hunter seeker starts diving onto its target.
see_also: [HunterSeekerDetonateProximity, HunterSeekerDescentSpeed, HunterSeekerAscentSpeed, HunterSeeker, "system:superweapons"]
when_omitted:
  kind: value
  value: "0"
---

Once a [hunter seeker](/systems/superweapons/#hunter-seeker) with a target is nearer than this to the coordinate it is flying to, measured flat across the map, its flight level is set between the altitude of its target and the level its type normally flies at, in proportion to how much of the range is left. At the outer edge the drone is still at its cruising level; arriving on the target it is at the target's own altitude; and the result is never allowed below 10 leptons above the ground. [`HunterSeekerDescentSpeed`](/keys/hunterseekerdescentspeed/) covers how quickly the drone actually gives up the altitude.

Further out than this the drone instead looks ten steps ahead along its heading and, when the highest ground it finds stands above the ground beneath it, sets its flight level to that peak's height plus its type's cruising height. Because that level is measured from the ground under the drone rather than from the peak, a drone approaching high ground climbs well past what clearing it would need. This figure is therefore the point at which terrain stops being avoided and the dive begins.

At the stored figure the measured distance can never fall below it, so the drone stays on the terrain-clearing path for the whole approach and never dives.

---
key: HunterSeekerAscentSpeed
summary: Leptons a hunter seeker climbs each frame once it is airborne.
see_also: [HunterSeekerEmergeSpeed, HunterSeekerDescentSpeed, HunterSeeker, "system:superweapons"]
when_omitted:
  kind: value
  value: "0"
---

Each frame an airborne [hunter seeker](/systems/superweapons/#hunter-seeker) sits below its flight level it rises by the smaller of this figure and the distance still to go. While a drone with a target is further from its destination than [`HunterSeekerDescendProximity`](/keys/hunterseekerdescendproximity/), it scans the ground along its heading and, when the highest ground it finds stands above the ground beneath it, sets its flight level to that peak's height plus its type's cruising height. That flight level is measured from the ground under the drone rather than from the peak, so a drone approaching high ground climbs well past what clearing it would need, and this figure decides whether the drone tops a ridge in its path or crawls up the face of it. The lift-off from the ground climbs at [`HunterSeekerEmergeSpeed`](/keys/hunterseekeremergespeed/) instead.

At the stored figure the step is zero, and a drone already at level flight never climbs again however high the ground ahead of it stands.

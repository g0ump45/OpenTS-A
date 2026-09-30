---
key: HunterSeekerDescentSpeed
summary: Leptons a hunter seeker drops each frame.
see_also: [HunterSeekerAscentSpeed, HunterSeekerEmergeSpeed, HunterSeekerDescendProximity, HunterSeeker, "system:superweapons"]
when_omitted:
  kind: value
  value: "0"
---

Each frame an airborne [hunter seeker](/systems/superweapons/#hunter-seeker) sits above its flight level it drops by the smaller of this figure and its height above the ground. That second limit is the drone's whole altitude rather than the gap down to the level it is heading for, so a figure larger than the gap carries it past that level in one step and leaves the climb to put it back. A drone reduced to no strength is pulled down by an accelerating fall of its own — one lepton on the first frame, two on the next, and so on — on top of whatever this figure takes off. It is destroyed the moment that fall carries it to the ground, throwing a blast of 1000 damage through [`C4Warhead`](/keys/c4warhead/) at its landing point.

The staged descent an ordinary aircraft makes — a twentieth of the remaining gap, held between 20 and 50 leptons a frame — is not applied to a hunter seeker at any point. [`HunterSeekerDescendProximity`](/keys/hunterseekerdescendproximity/) covers where the drone is told to descend to.

At the stored figure the step is zero and the drone holds whatever altitude it has reached.

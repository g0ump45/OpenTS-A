---
key: Accelerates
summary: Makes a driving vehicle ease up to speed and brake as it nears its destination.
see_also: ["AccelerationFactor", "DeaccelerationFactor", "SlowdownDistance"]
when_omitted:
  kind: value
  value: "yes"
---

Only the drive locomotor consults the flag. A type moved by any other [`Locomotor=`](/keys/locomotor/) travels at whatever speed its own locomotor asks for, whatever this says.

Cleared, the vehicle is set outright to the speed it has been told to hold, every step of the way: it reaches full speed in one frame and stops dead. Set, the speed is walked toward that target instead, by [`AccelerationFactor`](/keys/accelerationfactor/) while it is climbing and by [`DeaccelerationFactor`](/keys/deaccelerationfactor/) while it is falling, with the braking run beginning within [`SlowdownDistance`](/keys/slowdowndistance/) of the destination.

The passive test sits inside this flag's own branch, so a [`Passive=yes`](/keys/passive/) vehicle is skipped only there: the ramping never runs for it while the flag is set, while `Accelerates=no` still sets its throttle outright every step. A passive vehicle following another is driven from the front instead — the leading vehicle pushes its own speed onto every vehicle behind it as it ramps. The clamp that holds a vehicle to a fifth of its speed while it is crushing something sits inside the ramping branch, so a vehicle without the flag crushes at full speed.

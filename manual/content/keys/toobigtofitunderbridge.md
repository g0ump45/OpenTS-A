---
key: TooBigToFitUnderBridge
summary: Splits a vehicle's composed image into two separately sorted pieces while it passes under a bridge.
see_also: ["ZFudgeBridge", "ZFudgeColumn", "Turret"]
when_omitted:
  kind: value
  value: "no"
---

The flag changes drawing only, and only for a vehicle whose image is assembled from separate pieces before it goes on the screen: a shape-drawn vehicle needs [`Turret=yes`](/keys/turret/), and a voxel-drawn one needs either that with a turret voxel present or a barrel voxel of its own. Such a vehicle is composed on a scratch surface so that hull, turret and barrel layer correctly against one another, and this flag governs how the finished composite is then put down. A vehicle drawn in one piece never reaches that step, so the flag does nothing for it whatever its height.

When the flag is set and the branch applies, the composite goes down in two pieces — a band 32 pixels deep off the top, and the remainder below it — each with a depth bias and depth gradient of its own, so the upper and lower halves of the vehicle sort against the bridge deck independently instead of as one sprite.

Two conditions reach that split. The first is the vehicle being under a bridge — its own cell covered, or a covered cell alongside whose deck still reaches over it, exactly the test [`ZFudgeBridge`](/keys/zfudgebridge/) describes — with no bridge support tile registered beside it, the same neighbor count [`ZFudgeColumn`](/keys/zfudgecolumn/) covers. The second is the vehicle having a destination assigned while in radio contact with a [`WeaponsFactory=yes`](/keys/weaponsfactory/) building, which is the tall vehicle rolling out of the factory it was built in.

The whole flag is inert on a vehicle that is not under a bridge and not leaving a war factory: it neither restricts movement nor keeps the vehicle off a bridge cell.

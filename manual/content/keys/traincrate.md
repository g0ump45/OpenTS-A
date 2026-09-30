---
key: TrainCrate
summary: Whether a destroyed train vehicle drops a crate in this scenario.
see_also: ["system:crates"]
when_omitted:
  kind: value
  value: "no"
---

The setting gates the drop for every [`CarriesCrate=yes`](/keys/carriescrate/) vehicle whose type is [`IsTrain=yes`](/keys/istrain/); everything else uses [`TruckCrate`](/keys/truckcrate/) instead.

Unlike its counterpart, this setting can change during a mission: the [Toggle Train Cargo](/mapping/actions/taction-toggle-train-cargo/) trigger action flips it to the opposite state each time it runs, so a scenario can switch cargo trains on and off as the mission progresses.

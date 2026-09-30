---
key: TruckCrate
summary: Whether a destroyed non-train vehicle drops a crate in this scenario.
see_also: ["system:crates"]
when_omitted:
  kind: value
  value: "no"
---

The setting gates the drop for every [`CarriesCrate=yes`](/keys/carriescrate/) vehicle whose type is not a train; trains use [`TrainCrate`](/keys/traincrate/) instead. It is read once as the scenario loads and nothing changes it afterwards.

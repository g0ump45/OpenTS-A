---
key: VehicleThief
summary: Makes a soldier take the vehicle it is sent at, and lets it walk into that vehicle's cell.
see_also: ["system:capture"]
when_omitted:
  kind: value
  value: "no"
---

The cursor appears over any non-structure counted as a vehicle, a landed aircraft included, as long as the vehicle belongs to a different house — the test is house identity, not alliance, so an allied house's vehicle takes it too. An [`IsTrain=yes`](/keys/istrain/) type is excluded from every cursor, targeting and movement path the feature uses. [Stealing a vehicle](/systems/capture/#stealing-a-vehicle) covers what the arrival does.

Two effects outlive the theft. The stolen vehicle counts against this type's [`BuildLimit`](/keys/buildlimit/) for as long as it lives, so a hijacker limited to one cannot be rebuilt while its prize survives; and when that vehicle is destroyed the hijacker is recreated at the wreck, with a strength between 5 and half its maximum, regardless of [`Crewed`](/keys/crewed/).

The setting also changes what its owner scans for and what it will keep without scanning again, both covered by [target selection](/systems/target-selection/#what-each-kind-of-object-considers).

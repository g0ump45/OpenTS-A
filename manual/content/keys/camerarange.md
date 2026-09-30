---
key: CameraRange
summary: Parsed distance that the engine never uses.
no_effect: true
see_also: ["system:map-visibility"]
when_omitted:
  kind: value
  value: "9"
---

The value is written in cells and converted to leptons as it is read. Nothing reads it back and nothing falls back to it. The camera-weapon branch its name fits — an aircraft revealing ground instead of firing — is compiled out of the game, and that branch reveals a hard-coded nine cells rather than consulting this value.

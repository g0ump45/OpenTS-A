---
key: ComputerBaseDefenseResponse
summary: Multiplies an attacker's ThreatPosed to size the defenders a computer house calls up.
see_also: ["system:target-selection"]
when_omitted:
  kind: value
  value: "3"
---

When one of a computer house's buildings — or one of its [`ToProtect=yes`](/keys/toprotect/) objects — is damaged by enemy infantry or an enemy vehicle, the house sizes its response at the attacker's [`ThreatPosed`](/keys/threatposed/) multiplied by this value, then picks defenders from its own infantry and vehicles until that figure is covered. Anything already fighting that attacker is counted off it first. An attacker whose type leaves `ThreatPosed` at zero calls up nobody however large this value is.

The call-up is skipped for a human house, for an attacker that is an ally, for a building whose type is [`Insignificant=yes`](/keys/insignificant/) or that deploys back into a vehicle, and — in a campaign game only — for a building that carries a weapon of its own.

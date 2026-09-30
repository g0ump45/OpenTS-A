---
key: Disableable
summary: Parsed flag that the engine never uses.
no_effect: true
see_also: ["system:emp-pulse", "system:power", Powered]
when_omitted:
  kind: value
  value: "yes"
---

Nothing reads the stored flag, so no type can be exempted from being shut down this way. What actually shuts a structure down is decided elsewhere and consults none of it: [an EM pulse](/systems/emp-pulse/#what-a-pulse-reaches) powers off and stuns every building it catches except an invisible one, a limpet mine and a core defender, and a house short of power stops the functions of the structures that [`Powered=yes`](/keys/powered/) marks as needing it.

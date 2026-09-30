---
key: StartStateAI
summary: The animation state a particle is created at.
see_also: ["EndStateAI", "StateAIAdvance", "DeleteOnStateLimit"]
when_omitted:
  kind: value
  value: "0"
---

A particle's state doubles as the frame of its artwork that is drawn, so this is both where the sequence begins and which frame appears the first time the particle is visible. A `Fire` particle offsets that frame by the artwork bank its firing direction picks, and `Spark` and `Railgun` particles draw no artwork at all. The state is held in one signed byte, so a value above 127 wraps negative.

[`Smoke` and `Fire`](/keys/behaveslike/#scope-particletype) particles only advance while the state is below [`EndStateAI`](/keys/endstateai/), so starting at or above the end freezes the sequence for the particle's whole life — and with it the [`DeleteOnStateLimit`](/keys/deleteonstatelimit/) death and the [`Translucent25State`](/keys/translucent25state/) and [`Translucent50State`](/keys/translucent50state/) fades, none of which are ever reached. `Gas`, `WeakGas` and `Web` particles advance regardless of where they started, and when they wrap they restart at state 0 rather than at this one, so a type that starts partway into its sequence plays the opening frames on every loop after the first.

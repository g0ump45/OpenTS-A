---
key: StateAIAdvance
summary: The frames a particle spends in each animation state.
see_also: ["StartStateAI", "EndStateAI", "Normalized", "DeleteOnStateLimit"]
when_omitted:
  kind: value
  value: "4"
---

Particles of a type do not step together: those with an odd internal identifier hold each state one frame longer than this, and the count each particle is measured against is offset by that same identifier. A cloud spawned in one burst therefore drifts out of step within a few states instead of animating in lockstep. `Gas`, `WeakGas`, `Smoke`, `Fire` and `Web` particles all use the interval; `Spark` and `Railgun` particles have no state machine and ignore it.

A `Fire` particle marked [`Normalized=yes`](/keys/normalized/#scope-particletype) discards the figure and works its own interval out from its flight. That result is kept in one signed byte, so a computed interval above 127 wraps to a much smaller or negative one, and can land on `0` or `-1`. The figure written here is truncated to the same byte.

:::danger[Zero and -1 stop the game]
The interval is used as a divisor without a check, and half the particles of a type have one frame added to it first. At `0` the other half divide by zero on the first logic frame they run, and `-1` does the same to the half that has one added. A `Smoke` or `Fire` particle escapes only while its state already sits at the end of its sequence. Every other value, negative ones included, divides cleanly.
:::

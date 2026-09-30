---
key: FireProne
summary: The stage of the prone firing animation at which an infantry type releases its round.
see_also: ["FireUp", "Sequence", "Crawls"]
when_omitted:
  kind: value
  value: "0"
---

This is the same stage gate as [`FireUp`](/keys/fireup/), consulted instead of it while the soldier is prone. The figure counts stages of the run named `FireProne` in the type's [`Sequence`](/keys/sequence/) section, from `0`, and a figure beyond that run's frame count is never matched, so the soldier never releases its round while lying down.

A type that declares [`FireUp`](/keys/fireup/) but not this key releases prone shots on the first stage of its prone firing run, since the two are separate figures with separate defaults.

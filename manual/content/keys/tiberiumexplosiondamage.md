---
key: TiberiumExplosionDamage
summary: Damage a Tiberium chain-reaction animation deals where it stands.
see_also: ["system:tiberium", "Debris"]
when_omitted:
  kind: value
  value: "100"
---

An animation declaring [`TiberiumChainReaction=yes`](/keys/tiberiumchainreaction/) standing on Tiberium strips the cell bare and applies this figure through [`C4Warhead`](/keys/c4warhead/) at its own position. The figure is fixed: it does not scale with the Tiberium type, the growth stage removed, or the animation's own settings.

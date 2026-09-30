---
key: Translucency
scope: particletype
label: Particle fade
see_also: ["Translucent25State", "Translucent50State", "BehavesLike"]
when_omitted:
  kind: value
  value: "0"
---

Only three levels of translucency can be drawn, and the value has to land on one of them: 25 draws the particle a quarter faded, 50 a half, and 75 through 127 three quarters. Every other number draws the particle solid, `0` among them, and a figure of 128 or more wraps back into that range. The whole test is skipped below the High detail setting: at Medium detail particles are drawn solid whatever this says, and at Low detail smoke and spark particles are not drawn at all.

The figure is only where a particle starts. A [`Fire`](/keys/behaveslike/#scope-particletype) particle raises its own as its sequence passes [`Translucent25State`](/keys/translucent25state/) and [`Translucent50State`](/keys/translucent50state/), and a smoke system adds a step to nearly every successor it creates, and to the particles it emits once the plume has begun to thin — so a puff authored at `25` is usually drawn at `50`, and its successors more faded still.

`Spark` and `Railgun` particles are plotted as single pixels rather than drawn from artwork, and that path never consults the setting.

```ini title="rules.ini"
[MYSMOKEPUFF] ; a ParticleType registered in [Particles]
Image=SGRYSMK1
BehavesLike=Smoke
Translucency=25 ; a quarter faded when created, half once the plume thins
MaxEC=80
EndStateAI=20
```
